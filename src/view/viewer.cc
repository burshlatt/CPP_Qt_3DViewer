#include "viewer.h"

#include "ui_viewer.h"

namespace s21 {
Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
    ui_->setupUi(this);
    this->setFixedSize(310, 685);
    ogl_ = new OpenGL;
    ogl_->resize(900, 900);
    timer_ = new QTimer(0);
    parser_ = std::make_unique<Parser>(ogl_->get_data());

    connect(timer_, &QTimer::timeout, this, &Viewer::SaveGIF);
    connect(ui_->GIF, &QPushButton::clicked, this, &Viewer::CreateGIF);
    connect(ui_->Screen, &QPushButton::clicked, this, &Viewer::CreateScreenshot);
    connect(ui_->OpenFile, &QPushButton::clicked, this, &Viewer::OpenFile);
    connect(ui_->btnReset, &QPushButton::clicked, this, &Viewer::ResetSettings);
    connect(ui_->btnShowModel, &QPushButton::clicked, this, &Viewer::ShowModelPanel);
    connect(ui_->OXRotate, &QDial::valueChanged, this, &Viewer::RotateX);
    connect(ui_->OYRotate, &QDial::valueChanged, this, &Viewer::RotateY);
    connect(ui_->OZRotate, &QDial::valueChanged, this, &Viewer::RotateZ);
    connect(ui_->MColor, &QPushButton::clicked, this, &Viewer::SetMainColor);
    connect(ui_->LColor, &QPushButton::clicked, this, &Viewer::SetLineColor);
    connect(ui_->VColor, &QPushButton::clicked, this, &Viewer::SetVertexColor);
    connect(ui_->MYUp, &QPushButton::clicked, this, [this]() { Move(kUp); });
    connect(ui_->MZFar, &QPushButton::clicked, this, [this]() { Move(kFar); });
    connect(ui_->MYDown, &QPushButton::clicked, this, [this]() { Move(kDown); });
    connect(ui_->MXLeft, &QPushButton::clicked, this, [this]() { Move(kLeft); });
    connect(ui_->MXRight, &QPushButton::clicked, this, [this]() { Move(kRight); });
    connect(ui_->MZClose, &QPushButton::clicked, this, [this]() { Move(kClose); });
    connect(ui_->ScaleMinus, &QPushButton::clicked, this, [this]() { Scale(kFar); });
    connect(ui_->ScalePlus, &QPushButton::clicked, this, [this]() { Scale(kClose); });
    connect(ui_->LineSize, &QSpinBox::valueChanged, this, &Viewer::SetLineWidth);
    connect(ui_->VertexSize, &QSpinBox::valueChanged, this, &Viewer::SetVertexWidth);
    connect(ui_->cbModelType, &QComboBox::currentTextChanged, this, &Viewer::SetModelType);
    connect(ui_->cbShading, &QComboBox::currentTextChanged, this, &Viewer::SetShadingType);
    connect(ui_->cbVertexType, &QComboBox::currentTextChanged, this, &Viewer::SetVertexType);
    connect(ui_->cbProjection, &QComboBox::currentTextChanged, this, &Viewer::SetProjectionType);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->geometry();
    int x = (screen_geometry.width() - 275) / 1.2;
    int y = (screen_geometry.height() - 685) / 2;
    move(x, y);

    SetEnableComponent(false);
}

Viewer::~Viewer() {
    SaveSettings();
    ogl_->close();
    delete ui_;
    delete ogl_;
    delete timer_;
}

void Viewer::SaveSettings() {
    Options &opt = ogl_->get_opt();
    QSettings settings("School21", "3DViewer");
    settings.setValue("saved", 1);
    settings.setValue("line_color_r", opt.line_color.x());
    settings.setValue("line_color_g", opt.line_color.y());
    settings.setValue("line_color_b", opt.line_color.z());
    settings.setValue("main_color", opt.main_color.name());
    settings.setValue("vertex_color_r", opt.vertex_color.x());
    settings.setValue("vertex_color_g", opt.vertex_color.y());
    settings.setValue("vertex_color_b", opt.vertex_color.z());
    settings.setValue("line_size", ui_->LineSize->text());
    settings.setValue("vertex_size", ui_->VertexSize->text());
    settings.setValue("prj_type", ui_->cbProjection->currentText());
    settings.setValue("model_type", ui_->cbModelType->currentText());
    settings.setValue("vertex_type", ui_->cbVertexType->currentText());
}

void Viewer::LoadSettings() {
    QSettings settings("School21", "3DViewer");
    if (settings.value("saved").toInt() == 1) {
        Options &opt = ogl_->get_opt();
        QVector3D color_l = {
            settings.value("line_color_r").toFloat(),
            settings.value("line_color_g").toFloat(),
            settings.value("line_color_b").toFloat()
        };
        opt.line_color = color_l;
        QVector3D color_v = {
            settings.value("vertex_color_r").toFloat(),
            settings.value("vertex_color_g").toFloat(),
            settings.value("vertex_color_b").toFloat()
        };
        opt.vertex_color = color_v;
        QColor color_m(settings.value("main_color").toString());
        opt.main_color = color_m;

        ui_->LineSize->setValue(settings.value("line_size").toInt());
        ui_->VertexSize->setValue(settings.value("vertex_size").toInt());
        ui_->cbProjection->setCurrentText(settings.value("prj_type").toString());
        ui_->cbModelType->setCurrentText(settings.value("model_type").toString());
        ui_->cbVertexType->setCurrentText(settings.value("vertex_type").toString());
    }
}

void Viewer::OpenFile() {
    QString path = QFileDialog::getOpenFileName(nullptr, "Open File", QString(), "Obj Files (*.obj)");
    if (!path.isEmpty()) {
        ui_->degX->setText("0");
        ui_->degY->setText("0");
        ui_->degZ->setText("0");
        ui_->OXRotate->setValue(0);
        ui_->OYRotate->setValue(0);
        ui_->OZRotate->setValue(0);
        parser_->Parse(path.toStdString());
        Data &data = ogl_->get_data();
        ui_->FileName->setText(path.section('/', -1));
        ui_->VCount->setText(QString::number(data.vertexes_v.size() / 3));
        ui_->ECount->setText(QString::number(data.edges.size() / 2));
        ui_->FCount->setText(QString::number(data.f_count));
        SetEnableComponent(true);
        ShowModelPanel();
        ogl_->Start();

        QLayoutItem *item;
        while ((item = ui_->grid_layout_material->takeAt(0)) != nullptr) {
            QWidget *widget = item->widget();
            if (widget != nullptr)
                delete widget;
            delete item;
        }

        LoadMaterial();
        LoadSettings();
    }
}

void Viewer::SetEnableComponent(bool is_enable) {
    ui_->MYUp->setEnabled(is_enable);
    ui_->MZFar->setEnabled(is_enable);
    ui_->MXLeft->setEnabled(is_enable);
    ui_->MYDown->setEnabled(is_enable);
    ui_->MColor->setEnabled(is_enable);
    ui_->LColor->setEnabled(is_enable);
    ui_->VColor->setEnabled(is_enable);
    ui_->MXRight->setEnabled(is_enable);
    ui_->MZClose->setEnabled(is_enable);
    ui_->OXRotate->setEnabled(is_enable);
    ui_->OYRotate->setEnabled(is_enable);
    ui_->OZRotate->setEnabled(is_enable);
    ui_->LineSize->setEnabled(is_enable);
    ui_->btnReset->setEnabled(is_enable);
    ui_->cbShading->setEnabled(is_enable);
    ui_->ScalePlus->setEnabled(is_enable);
    ui_->VertexSize->setEnabled(is_enable);
    ui_->ScaleValue->setEnabled(is_enable);
    ui_->ScaleMinus->setEnabled(is_enable);
    ui_->XMoveValue->setEnabled(is_enable);
    ui_->YMoveValue->setEnabled(is_enable);
    ui_->ZMoveValue->setEnabled(is_enable);
    ui_->cbModelType->setEnabled(is_enable);
    ui_->cbProjection->setEnabled(is_enable);
    ui_->cbVertexType->setEnabled(is_enable);
    ui_->btnShowModel->setEnabled(is_enable);
}

void Viewer::ShowModelPanel() {
    if (!ui_->FileName->text().isEmpty()) {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screen_geometry = screen->geometry();
        int x = (screen_geometry.width() - 275) / 1.2 - 950;
        int y = (screen_geometry.height() - 900) / 2;
        ogl_->show();
        ogl_->move(x, y);
    }
}

void Viewer::ResetSettings() {
    ui_->LineSize->setValue(0);
    ui_->VertexSize->setValue(0);
    ui_->cbShading->setCurrentText("Smooth");
    ui_->cbModelType->setCurrentText("Frame");
    ui_->cbVertexType->setCurrentText("None");
    ui_->cbProjection->setCurrentText("Parallel");

    ogl_->set_line_size(1.0f);
    ogl_->set_vertex_size(1.0f);
    ogl_->set_model_type(kFrame);
    ogl_->set_vertex_type(kNone);
    ogl_->set_shading_type(kSmooth);
    ogl_->set_projection(kParallel);
    ogl_->set_main_color("#686868");
    ogl_->set_line_color({1.0f, 1.0f, 1.0f});
    ogl_->set_vertex_color({1.0f, 1.0f, 1.0f});
}

void Viewer::Move(Action act) {
    if (act == kLeft)
        ogl_->Move(-ui_->XMoveValue->text().replace(",", ".").toDouble(), kX);
    else if (act == kRight)
        ogl_->Move(ui_->XMoveValue->text().replace(",", ".").toDouble(), kX);
    else if (act == kUp)
        ogl_->Move(ui_->YMoveValue->text().replace(",", ".").toDouble(), kY);
    else if (act == kDown)
        ogl_->Move(-ui_->YMoveValue->text().replace(",", ".").toDouble(), kY);
    else if (act == kClose)
        ogl_->Move(-ui_->ZMoveValue->text().replace(",", ".").toDouble(), kZ);
    else if (act == kFar)
        ogl_->Move(ui_->ZMoveValue->text().replace(",", ".").toDouble(), kZ);
}

void Viewer::Scale(Action act) {
    if (act == kClose)
        ogl_->Scale(ui_->ScaleValue->text().replace(",", ".").toDouble(), kScaleMul);
    else if (act == kFar)
        ogl_->Scale(ui_->ScaleValue->text().replace(",", ".").toDouble(), kScaleDiv);
}

void Viewer::RotateX(int value) {
    if (value > check_x_) {
        ogl_->Rotate(1.0, kX);
        deg_x_++;
    } else {
        ogl_->Rotate(-1.0, kX);
        deg_x_--;
    }
    ui_->degX->setText(QString::number(deg_x_));
    check_x_ = value;
}

void Viewer::RotateY(int value) {
    if (value > check_y_) {
        ogl_->Rotate(1.0, kY);
        deg_y_++;
    } else {
        ogl_->Rotate(-1.0, kY);
        deg_y_--;
    }
    ui_->degY->setText(QString::number(deg_y_));
    check_y_ = value;
}

void Viewer::RotateZ(int value) {
    if (value > check_z_) {
        ogl_->Rotate(-1.0, kZ);
        deg_z_++;
    } else {
        ogl_->Rotate(1.0, kZ);
        deg_z_--;
    }
    ui_->degZ->setText(QString::number(deg_z_));
    check_z_ = value;
}

void Viewer::SetProjectionType() {
    if (ui_->cbProjection->currentText() == "Parallel")
        ogl_->set_projection(kParallel);
    else if (ui_->cbProjection->currentText() == "Central")
        ogl_->set_projection(kCentral);
}

void Viewer::SetVertexWidth() {
    ogl_->set_vertex_size(ui_->VertexSize->text().toDouble());
}

void Viewer::SetLineWidth() {
    ogl_->set_line_size(ui_->LineSize->text().toDouble());
}

void Viewer::SetModelType() {
    if (ui_->cbModelType->currentText() == "Frame")
        ogl_->set_model_type(kFrame);
    else if (ui_->cbModelType->currentText() == "Dashed")
        ogl_->set_model_type(kDashed);
    else if (ui_->cbModelType->currentText() == "Solid")
        ogl_->set_model_type(kSolid);
    else if (ui_->cbModelType->currentText() == "Textured")
        ogl_->set_model_type(kTextured);
}

void Viewer::SetVertexType() {
    if (ui_->cbVertexType->currentText() == "None")
        ogl_->set_vertex_type(kNone);
    else if (ui_->cbVertexType->currentText() == "Quad")
        ogl_->set_vertex_type(kSquare);
    else if (ui_->cbVertexType->currentText() == "Circle")
        ogl_->set_vertex_type(kCircle);
}

void Viewer::SetShadingType() {
    if (ui_->cbShading->currentText() == "Smooth")
        ogl_->set_shading_type(kSmooth);
    else if (ui_->cbShading->currentText() == "Flat")
        ogl_->set_shading_type(kFlat);
}

void Viewer::SetLineColor() {
    QColor color_line = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_line.isValid()) {
        QVector3D color = {
            color_line.redF(),
            color_line.greenF(),
            color_line.blueF()
        };
        ogl_->set_line_color(color);
    }
}

void Viewer::SetVertexColor() {
    QColor color_vertex = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_vertex.isValid()) {
        QVector3D color = {
            color_vertex.redF(),
            color_vertex.greenF(),
            color_vertex.blueF()
        };
        ogl_->set_vertex_color(color);
    }
}

void Viewer::SetMainColor() {
    QColor color_main = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_main.isValid())
        ogl_->set_main_color(color_main);
}

void Viewer::CreateScreenshot() {
    QString f_name = QFileDialog::getSaveFileName(this, "Save screenshot", "", "BMP Image (*.bmp);; JPEG Image (*.jpeg)");
    if (f_name != "") {
        QImage img = ogl_->get_frame();
        img.save(f_name);
    }
}

void Viewer::CreateGIF() {
    gif_name_ = QFileDialog::getSaveFileName(this, "Save GIF", "", "Gif Files (*.gif)");
    if (gif_name_ != "") {
        ui_->GIF->setText("▢");
        ui_->GIF->setDisabled(true);
        frame_ = new QGifImage;
        frame_->setDefaultDelay(10);
        timer_->setInterval(100);
        timer_->start();
    }
}

void Viewer::SaveGIF() {
    QImage img = ogl_->get_frame();
    frame_->addFrame(img);
    if (frame_count_ == 50) {
        timer_->stop();
        frame_->save(gif_name_);
        frame_count_ = 0;
        delete frame_;
        ui_->GIF->setEnabled(true);
        ui_->GIF->setText("GIF ▶");
    }
    frame_count_++;
}

void Viewer::SetInfo(const QString &name, const QString &info) {
    QLabel *new_label = new QLabel(ui_->scroll_area_maps->widget());
    new_label->setText(name + info);
    new_label->setWordWrap(true);
    new_label->setAlignment(Qt::AlignCenter);
    new_label->setStyleSheet("QLabel { color: white; }");
    ui_->grid_layout_material->addWidget(new_label);
}

void Viewer::SetImg(const Mtl &mtl, const QString &img_path, MapType map_type, int idx) {
    SetInfo("========================", "");
    SetInfo("Name:\n", QString::fromStdString(mtl.name) + "\n");

    if (map_type == kAmbient) {
        QString ka = "";
        for (int i = 0; i < 3; i++)
            ka += QString::number(mtl.Ka[i]) + " ";
        SetInfo("Ambient: ", ka);
    } else if (map_type == kDiffuse) {
        QString kd = "";
        for (int i = 0; i < 3; i++)
            kd += QString::number(mtl.Kd[i]) + " ";
        SetInfo("Diffuse: ", kd);
    } else if (map_type == kSpecular) {
        QString ks = "";
        for (int i = 0; i < 3; i++)
            ks += QString::number(mtl.Ks[i]) + " ";
        SetInfo("Diffuse: ", ks);
    }
    QString ke = "";
    for (int i = 0; i < 3; i++)
        ke += QString::number(mtl.Ke[i]) + " ";

    SetInfo("Emmission: ", ke);
    SetInfo("Opacity: ", QString::number(mtl.d));
    SetInfo("Shiness: ", QString::number(mtl.Ns));
    SetInfo("\nTexture:", "");

    QPushButton *show_img = new QPushButton();
    QPushButton *btn_save = new QPushButton();
    QPushButton *btn_load = new QPushButton();
    QPushButton *btn_unload = new QPushButton();
    show_img->setText("Show img");
    btn_save->setText("Save UV");
    btn_load->setText("Load texture");
    btn_unload->setText("Unload texture");
    show_img->setStyleSheet(
        "QPushButton {background-color: #8F8F8F; border-radius: 2px; border: 2px "
        "solid gray; color: white;} QPushButton:hover {border: 2px solid "
        "#69A1E4;} QPushButton:pressed {background-color: white;}");
    btn_save->setStyleSheet(
        "QPushButton {background-color: #8F8F8F; border-radius: 2px; border: 2px "
        "solid gray; color: white;} QPushButton:hover {border: 2px solid "
        "#69A1E4;} QPushButton:pressed {background-color: white;}");
    btn_load->setStyleSheet(
        "QPushButton {background-color: #8F8F8F; border-radius: 2px; border: 2px "
        "solid gray; color: white;} QPushButton:hover {border: 2px solid "
        "#69A1E4;} QPushButton:pressed {background-color: white;}");
    btn_unload->setStyleSheet(
        "QPushButton {background-color: #8F8F8F; border-radius: 2px; border: 2px "
        "solid gray; color: white;} QPushButton:hover {border: 2px solid "
        "#69A1E4;} QPushButton:pressed {background-color: white;}");
    ui_->grid_layout_material->addWidget(show_img);
    ui_->grid_layout_material->addWidget(btn_save);
    ui_->grid_layout_material->addWidget(btn_load);
    ui_->grid_layout_material->addWidget(btn_unload);

    connect(show_img, &QPushButton::clicked, this, [this, img_path]() {
        QDialog *img_dialog = new QDialog(this);
        img_dialog->setWindowTitle("Image Viewer");
        QLabel *img_label = new QLabel(img_dialog);
        QPixmap img_pixmap(img_path);
        img_label->setPixmap(img_pixmap);
        img_label->setScaledContents(true);
        QVBoxLayout *layout = new QVBoxLayout(img_dialog);
        layout->addWidget(img_label);
        img_dialog->exec();
    });

    connect(btn_save, &QPushButton::clicked, this, [this, idx, img_path]() {
        QString save_path = QFileDialog::getSaveFileName(this, tr("Save UV-map"), QDir::homePath(), tr("PNG files (*.bmp)"));
        if (!save_path.isEmpty())
            ogl_->SaveUvMap(idx, img_path.toStdString(), save_path);
    });

    connect(btn_load, &QPushButton::clicked, this, [this, btn_unload, btn_save, show_img, map_type, idx]() {
        QString file_path = QFileDialog::getOpenFileName(this, tr("Load texture"), QDir::homePath(), tr("PNG files (*.bmp)"));
        if (!file_path.isEmpty()) {
            ogl_->ResetTexture(idx, map_type, file_path);
            show_img->setEnabled(true);
            btn_save->setEnabled(true);
            btn_unload->setEnabled(true);

            show_img->disconnect();
            connect(show_img, &QPushButton::clicked, this, [this, file_path]() {
                QDialog *img_dialog = new QDialog(this);
                img_dialog->setWindowTitle("Image Viewer");
                QLabel *img_label = new QLabel(img_dialog);
                QPixmap img_pixmap(file_path);
                img_label->setPixmap(img_pixmap);
                img_label->setScaledContents(true);
                QVBoxLayout *layout = new QVBoxLayout(img_dialog);
                layout->addWidget(img_label);
                img_dialog->exec();
            });

            btn_save->disconnect();
            connect(btn_save, &QPushButton::clicked, this, [this, idx, file_path]() {
                QString save_path = QFileDialog::getSaveFileName(this, tr("Save UV-map"), QDir::homePath(), tr("PNG files (*.png)"));
                ogl_->SaveUvMap(idx, file_path.toStdString(), save_path);
            });
        }
    });

    connect(btn_unload, &QPushButton::clicked, this, [this, btn_unload, btn_save, show_img, map_type, idx]() {
        ogl_->ResetTexture(idx, map_type);
        show_img->setEnabled(false);
        btn_save->setEnabled(false);
        btn_unload->setEnabled(false);
    });
}

void Viewer::LoadMaterial() {
    Data &data = ogl_->get_data();
    if (!data.mtl.empty()) {
        int index = 0;
        for (const auto &it : data.mtl) {
            if (!it.map_ka.empty())
                SetImg(it, QString::fromStdString(it.map_ka), kAmbient, index);
            if (!it.map_kd.empty())
                SetImg(it, QString::fromStdString(it.map_kd), kDiffuse, index);
            if (!it.map_ks.empty())
                SetImg(it, QString::fromStdString(it.map_ks), kSpecular, index);

            index++;
        }
    }
}
}  // namespace s21

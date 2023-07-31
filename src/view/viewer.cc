#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
    ui_->setupUi(this);
    this->setFixedSize(1100, 650);

    QScreen *screen_ = QGuiApplication::primaryScreen();
    QRect screen_geometry_ = screen_->geometry();
    int x_ = (screen_geometry_.width() - 1100) / 2;
    int y_ = (screen_geometry_.height() - 650) / 2;
    move(x_, y_);

    settings_ = new QSettings(this);
    if (settings_->value("saved").toInt() == 1) {
        LoadSettings();
    }

    connect(ui_->OpenFile, SIGNAL(clicked()), this, SLOT(OpenFile()));

    connect(ui_->MYUp, SIGNAL(clicked()), this, SLOT(MoveYU()));
    connect(ui_->MZFar, SIGNAL(clicked()), this, SLOT(MoveZF()));
    connect(ui_->MXLeft, SIGNAL(clicked()), this, SLOT(MoveXL()));
    connect(ui_->MYDown, SIGNAL(clicked()), this, SLOT(MoveYD()));
    connect(ui_->MZClose, SIGNAL(clicked()), this, SLOT(MoveZC()));
    connect(ui_->MXRight, SIGNAL(clicked()), this, SLOT(MoveXR()));

    connect(ui_->MColor, SIGNAL(clicked()), this, SLOT(MainColor()));
    connect(ui_->LColor, SIGNAL(clicked()), this, SLOT(LineColor()));
    connect(ui_->VColor, SIGNAL(clicked()), this, SLOT(VertexColor()));

    connect(ui_->ScalePlus, SIGNAL(clicked()), this, SLOT(ScaleMul()));
    connect(ui_->ScaleMinus, SIGNAL(clicked()), this, SLOT(ScaleDiv()));

    connect(ui_->LWPlus, SIGNAL(clicked()), this, SLOT(LWidthPlus()));
    connect(ui_->VWPlus, SIGNAL(clicked()), this, SLOT(VWidthPlus()));
    connect(ui_->LWMinus, SIGNAL(clicked()), this, SLOT(LWidthMinus()));
    connect(ui_->VWMinus, SIGNAL(clicked()), this, SLOT(VWidthMinus()));

    connect(ui_->StippleNo, SIGNAL(clicked()), this, SLOT(StippleType()));
    connect(ui_->StippleYes, SIGNAL(clicked()), this, SLOT(StippleType()));

    connect(ui_->VertexNo, SIGNAL(clicked()), this, SLOT(VertexType()));
    connect(ui_->VertexCircle, SIGNAL(clicked()), this, SLOT(VertexType()));
    connect(ui_->VertexSquare, SIGNAL(clicked()), this, SLOT(VertexType()));

    connect(ui_->Central, SIGNAL(clicked()), this, SLOT(ProjectionType()));
    connect(ui_->Parallel, SIGNAL(clicked()), this, SLOT(ProjectionType()));

    connect(ui_->GIF, SIGNAL(clicked()), this, SLOT(CreateGIF()));
    connect(ui_->Screen, SIGNAL(clicked()), this, SLOT(CreateScreenshot()));

    QObject::connect(ui_->OXRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateX(int)));
    QObject::connect(ui_->OYRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateY(int)));
    QObject::connect(ui_->OZRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateZ(int)));
}

Viewer::~Viewer() {
    SaveSettings();
    delete ui_;
    delete settings_;
}

void Viewer::SaveSettings() noexcept {
    settings_->setValue("saved", 1);

    settings_->setValue("line_width", l_width_);
    settings_->setValue("vertex_width", v_width_);

    settings_->setValue("color_main_r", color_main_.redF());
    settings_->setValue("color_main_g", color_main_.greenF());
    settings_->setValue("color_main_b", color_main_.blueF());
    settings_->setValue("color_main_a", color_main_.alphaF());

    settings_->setValue("color_line_r", color_line_.redF());
    settings_->setValue("color_line_g", color_line_.greenF());
    settings_->setValue("color_line_b", color_line_.blueF());

    settings_->setValue("color_vertex_r", color_vertex_.redF());
    settings_->setValue("color_vertex_g", color_vertex_.greenF());
    settings_->setValue("color_vertex_b", color_vertex_.blueF());

    settings_->setValue("scale", ui_->ScaleValue->text());

    settings_->setValue("move_ox", ui_->XMoveValue->text());
    settings_->setValue("move_oy", ui_->YMoveValue->text());
    settings_->setValue("move_oz", ui_->ZMoveValue->text());

    settings_->setValue("central_prj", ui_->Central->isChecked());
    settings_->setValue("parallel_prj", ui_->Parallel->isChecked());

    settings_->setValue("line_stipple_no", ui_->StippleNo->isChecked());
    settings_->setValue("line_stipple_yes", ui_->StippleYes->isChecked());

    settings_->setValue("vertex_no", ui_->VertexNo->isChecked());
    settings_->setValue("vertex_circle", ui_->VertexCircle->isChecked());
    settings_->setValue("vertex_square", ui_->VertexSquare->isChecked());
}

void Viewer::LoadSettings() noexcept {
    l_width_ = settings_->value("line_width").toDouble();
    v_width_ = settings_->value("vertex_width").toDouble();

    double r_ = settings_->value("color_main_r").toDouble();
    double g_ = settings_->value("color_main_g").toDouble();
    double b_ = settings_->value("color_main_b").toDouble();
    color_main_ = QColor::fromRgbF(r_, g_, b_);
    r_ = settings_->value("color_line_r").toDouble();
    g_ = settings_->value("color_line_g").toDouble();
    b_ = settings_->value("color_line_b").toDouble();
    color_line_ = QColor::fromRgbF(r_, g_, b_);
    r_ = settings_->value("color_vertex_r").toDouble();
    g_ = settings_->value("color_vertex_g").toDouble();
    b_ = settings_->value("color_vertex_b").toDouble();
    color_vertex_ = QColor::fromRgbF(r_, g_, b_);

    ui_->Central->setChecked(settings_->value("central_prj", true).toBool());
    ui_->Parallel->setChecked(settings_->value("parallel_prj", true).toBool());
    ui_->VertexNo->setChecked(settings_->value("vertex_no", true).toBool());
    ui_->VertexCircle->setChecked(settings_->value("vertex_circle", true).toBool());
    ui_->VertexSquare->setChecked(settings_->value("vertex_square", true).toBool());
    ui_->StippleNo->setChecked(settings_->value("line_stipple_no", true).toBool());
    ui_->StippleYes->setChecked(settings_->value("line_stipple_yes", true).toBool());

    ui_->OGL->set_line_width(l_width_);
    ui_->OGL->set_vertex_width(v_width_);
    ui_->OGL->set_main_color(color_main_);
    ui_->OGL->set_line_color(color_line_);
    ui_->OGL->set_vertex_color(color_vertex_);
    VertexType();
    StippleType();
    ProjectionType();

    ui_->ScaleValue->setText(settings_->value("scale").toString());

    ui_->XMoveValue->setText(settings_->value("move_ox").toString());
    ui_->YMoveValue->setText(settings_->value("move_oy").toString());
    ui_->ZMoveValue->setText(settings_->value("move_oz").toString());
}

void Viewer::OpenFile() noexcept {
    QString path_ = QFileDialog::getOpenFileName(nullptr, "Open File", QString(), "Obj Files (*.obj)");
    if (!path_.isEmpty()) {
        parser_.Parse(path_.toStdString());
        data_ = parser_.get_data();
        ui_->OGL->set_data(data_);
        ui_->FileName->setText(path_);
        ui_->VCount->setText(QString::number(data_.v_count_));
        ui_->FCount->setText(QString::number(data_.f_count_));
        ui_->OGL->Update();
    }
}

void Viewer::MoveXL() noexcept {
    if (!ui_->XMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->XMoveValue->text().toDouble() * -1, 0);
        ui_->OGL->Update();
    }
}

void Viewer::MoveXR() noexcept {
    if (!ui_->XMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->XMoveValue->text().toDouble(), 0);
        ui_->OGL->Update();
    }
}

void Viewer::MoveYD() noexcept {
    if (!ui_->YMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->YMoveValue->text().toDouble() * -1, 1);
        ui_->OGL->Update();
    }
}

void Viewer::MoveYU() noexcept {
    if (!ui_->YMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->YMoveValue->text().toDouble(), 1);
        ui_->OGL->Update();
    }
}

void Viewer::MoveZC() noexcept {
    if (!ui_->ZMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->ZMoveValue->text().toDouble() * -1, 2);
        ui_->OGL->Update();
    }
}

void Viewer::MoveZF() noexcept {
    if (!ui_->ZMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->ZMoveValue->text().toDouble(), 2);
        ui_->OGL->Update();
    }
}

void Viewer::RotateX(const int &value) noexcept {
    if (value > check_x_)
        ui_->OGL->Rotate(0.1, 0);
    else
        ui_->OGL->Rotate(-0.1, 0);
    check_x_ = value;
    ui_->OGL->Update();
}

void Viewer::RotateY(const int &value) noexcept {
    if (value > check_y_)
        ui_->OGL->Rotate(0.1, 1);
    else
        ui_->OGL->Rotate(-0.1, 1);
    check_y_ = value;
    ui_->OGL->Update();
}

void Viewer::RotateZ(const int &value) noexcept {
    if (value > check_z_)
        ui_->OGL->Rotate(-0.1, 2);
    else
        ui_->OGL->Rotate(0.1, 2);
    check_z_ = value;
    ui_->OGL->Update();
}

void Viewer::ScaleMul() noexcept {
    ui_->OGL->ScaleMul(ui_->ScaleValue->text().toDouble());
    ui_->OGL->Update();
}

void Viewer::ScaleDiv() noexcept {
    ui_->OGL->ScaleDiv(ui_->ScaleValue->text().toDouble());
    ui_->OGL->Update();
}

void Viewer::ProjectionType() noexcept {
    if (ui_->Parallel->isChecked())
        ui_->OGL->set_parallel(true);
    else
        ui_->OGL->set_parallel(false);
    ui_->OGL->Update();
}

void Viewer::LineColor() noexcept {
    color_line_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_line_.isValid())
        ui_->OGL->set_line_color(color_line_);
    ui_->OGL->Update();
}

void Viewer::VertexColor() noexcept {
    color_vertex_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_vertex_.isValid())
        ui_->OGL->set_vertex_color(color_vertex_);
    ui_->OGL->Update();
}

void Viewer::MainColor() noexcept {
    color_main_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_main_.isValid())
        ui_->OGL->set_main_color(color_main_);
    ui_->OGL->Update();
}

void Viewer::LWidthPlus() noexcept {
    l_width_ += 0.5;
    ui_->OGL->set_line_width(l_width_);
    ui_->OGL->Update();
}

void Viewer::LWidthMinus() noexcept {
    if (l_width_ > 1)
        l_width_ -= 0.5;
    ui_->OGL->set_line_width(l_width_);
    ui_->OGL->Update();
}

void Viewer::VWidthPlus() noexcept {
    v_width_ += 0.5;
    ui_->OGL->set_vertex_width(v_width_);
    ui_->OGL->Update();
}

void Viewer::VWidthMinus() noexcept {
    if (v_width_ > 1)
        v_width_ -= 0.5;
    ui_->OGL->set_vertex_width(v_width_);
    ui_->OGL->Update();
}

void Viewer::StippleType() noexcept {
    if (ui_->StippleYes->isChecked())
        ui_->OGL->set_stipple(true);
    else
        ui_->OGL->set_stipple(false);
    ui_->OGL->Update();
}

void Viewer::VertexType() noexcept {
    if (ui_->VertexNo->isChecked())
        ui_->OGL->set_vertex_type(true, false);
    else if (ui_->VertexCircle->isChecked())
        ui_->OGL->set_vertex_type(false, true);
    else
        ui_->OGL->set_vertex_type(false, false);
    ui_->OGL->Update();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|

void Viewer::CreateScreenshot() noexcept {
  ui_->OGL->CreateScreenshot();
}

void Viewer::CreateGIF() noexcept {
  ui_->OGL->CreateGIF();
}

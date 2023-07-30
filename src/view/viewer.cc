#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
    ui_->setupUi(this);
    this->setFixedSize(1400, 590);

    QScreen *screen_ = QGuiApplication::primaryScreen();
    QRect screen_geometry_ = screen_->geometry();
    int x_ = (screen_geometry_.width() - 1400) / 2;
    int y_ = (screen_geometry_.height() - 590) / 2;
    move(x_, y_);

    connect(ui_->MYUp, SIGNAL(clicked()), this, SLOT(MoveYU()));
    connect(ui_->MZFar, SIGNAL(clicked()), this, SLOT(MoveZF()));
    connect(ui_->MXLeft, SIGNAL(clicked()), this, SLOT(MoveXL()));
    connect(ui_->MYDown, SIGNAL(clicked()), this, SLOT(MoveYD()));
    connect(ui_->MZClose, SIGNAL(clicked()), this, SLOT(MoveZC()));
    connect(ui_->MXRight, SIGNAL(clicked()), this, SLOT(MoveXR()));
    connect(ui_->LColor, SIGNAL(clicked()), this, SLOT(LineColor()));
    connect(ui_->VertexNo, SIGNAL(clicked()), this, SLOT(VertexNo()));
    connect(ui_->OpenFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(ui_->LWPlus, SIGNAL(clicked()), this, SLOT(LWidthPlus()));
    connect(ui_->VWPlus, SIGNAL(clicked()), this, SLOT(VWidthPlus()));
    connect(ui_->VColor, SIGNAL(clicked()), this, SLOT(VertexColor()));
    connect(ui_->ScalePlus, SIGNAL(clicked()), this, SLOT(ScaleMul()));
    connect(ui_->Central, SIGNAL(clicked()), this, SLOT(CentralPrj()));
    connect(ui_->ScaleMinus, SIGNAL(clicked()), this, SLOT(ScaleDiv()));
    connect(ui_->StippleNo, SIGNAL(clicked()), this, SLOT(StippleNo()));
    connect(ui_->LWMinus, SIGNAL(clicked()), this, SLOT(LWidthMinus()));
    connect(ui_->VWMinus, SIGNAL(clicked()), this, SLOT(VWidthMinus()));
    connect(ui_->Parallel, SIGNAL(clicked()), this, SLOT(ParallelPrj()));
    connect(ui_->StippleYes, SIGNAL(clicked()), this, SLOT(StippleYes()));
    connect(ui_->VertexCircle, SIGNAL(clicked()), this, SLOT(VertexCircle()));
    connect(ui_->VertexSquare, SIGNAL(clicked()), this, SLOT(VertexSquare()));
    QObject::connect(ui_->OXRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateX()));
    QObject::connect(ui_->OYRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateY()));
    QObject::connect(ui_->OZRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateZ()));
}

Viewer::~Viewer() {
  delete ui_;
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
    }
}

void Viewer::MoveXL() noexcept {
    if (!ui_->XMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->XMoveValue->text().toDouble() * -1, 0);
    }
}

void Viewer::MoveXR() noexcept {
    if (!ui_->XMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->XMoveValue->text().toDouble(), 0);
    }
}

void Viewer::MoveYD() noexcept {
    if (!ui_->YMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->YMoveValue->text().toDouble() * -1, 1);
    }
}

void Viewer::MoveYU() noexcept {
    if (!ui_->YMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->YMoveValue->text().toDouble(), 1);
    }
}

void Viewer::MoveZC() noexcept {
    if (!ui_->ZMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->ZMoveValue->text().toDouble() * -1, 2);
    }
}

void Viewer::MoveZF() noexcept {
    if (!ui_->ZMoveValue->text().isEmpty()) {
        ui_->OGL->Move(ui_->ZMoveValue->text().toDouble(), 2);
    }
}

void Viewer::RotateX() noexcept {
    ui_->OGL->Rotate(0.1, 0);
}

void Viewer::RotateY() noexcept {
    ui_->OGL->Rotate(0.1, 1);
}

void Viewer::RotateZ() noexcept {
    ui_->OGL->Rotate(0.1, 2);
}

void Viewer::ScaleMul() noexcept {
    ui_->OGL->ScaleMul(ui_->ScaleValue->text().toDouble());
}

void Viewer::ScaleDiv() noexcept {
    ui_->OGL->ScaleDiv(ui_->ScaleValue->text().toDouble());
}

void Viewer::ParallelPrj() noexcept {
    ui_->OGL->set_parallel(true);
}

void Viewer::CentralPrj() noexcept {
    ui_->OGL->set_parallel(false);
}

void Viewer::StippleYes() noexcept {
    ui_->OGL->set_stipple(true);
}

void Viewer::StippleNo() noexcept {
    ui_->OGL->set_stipple(false);
}

void Viewer::LineColor() noexcept {
    QColor color_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_.isValid())
        ui_->OGL->set_line_color(color_);
}

void Viewer::VertexColor() noexcept {
    QColor color_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color_.isValid())
        ui_->OGL->set_vertex_color(color_);
}

void Viewer::LWidthPlus() noexcept {
    l_width_ += 0.5;
    ui_->OGL->set_line_width(l_width_);
}

void Viewer::LWidthMinus() noexcept {
    if (l_width_ > 1)
        l_width_ -= 0.5;
    ui_->OGL->set_line_width(l_width_);
}

void Viewer::VWidthPlus() noexcept {
    v_width_ += 0.5;
    ui_->OGL->set_vertex_width(v_width_);
}

void Viewer::VWidthMinus() noexcept {
    if (v_width_ > 1)
        v_width_ -= 0.5;
    ui_->OGL->set_vertex_width(v_width_);
}

void Viewer::VertexNo() noexcept {
    ui_->OGL->set_vertex_type(true, false);
}

void Viewer::VertexCircle() noexcept {
    ui_->OGL->set_vertex_type(false, true);
}

void Viewer::VertexSquare() noexcept {
    ui_->OGL->set_vertex_type(false, false);
}

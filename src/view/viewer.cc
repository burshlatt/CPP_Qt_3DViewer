#include "viewer.h"
#include "ui_viewer.h"

namespace s21 {
Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
  ui_->setupUi(this);
  this->setFixedSize(1100, 650);
  controller_ = std::make_unique<Controller>(ui_->OGL->get_data());
  timer_ = new QTimer(0);
  SetConnections();
  SetPosition();
  SetSettings();
}

Viewer::~Viewer() {
  SaveSettings();
  delete ui_;
  delete timer_;
  delete settings_;
}

void Viewer::SetPosition() {
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screen_geometry = screen->geometry();
  int x = (screen_geometry.width() - 1100) / 2;
  int y = (screen_geometry.height() - 650) / 2;
  move(x, y);
}

void Viewer::SetSettings() {
  settings_ = new QSettings(this);
  if (settings_->value("saved").toInt() == 1) LoadSettings();
}

void Viewer::SetConnections() noexcept {
  connect(timer_, SIGNAL(timeout()), this, SLOT(SaveGIF()));
  connect(ui_->MYUp, SIGNAL(clicked()), this, SLOT(MoveYU()));
  connect(ui_->MZFar, SIGNAL(clicked()), this, SLOT(MoveZF()));
  connect(ui_->MXLeft, SIGNAL(clicked()), this, SLOT(MoveXL()));
  connect(ui_->MYDown, SIGNAL(clicked()), this, SLOT(MoveYD()));
  connect(ui_->GIF, SIGNAL(clicked()), this, SLOT(CreateGIF()));
  connect(ui_->MZClose, SIGNAL(clicked()), this, SLOT(MoveZC()));
  connect(ui_->MXRight, SIGNAL(clicked()), this, SLOT(MoveXR()));
  connect(ui_->MColor, SIGNAL(clicked()), this, SLOT(MainColor()));
  connect(ui_->LColor, SIGNAL(clicked()), this, SLOT(LineColor()));
  connect(ui_->OpenFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
  connect(ui_->LWPlus, SIGNAL(clicked()), this, SLOT(LWidthPlus()));
  connect(ui_->VWPlus, SIGNAL(clicked()), this, SLOT(VWidthPlus()));
  connect(ui_->VColor, SIGNAL(clicked()), this, SLOT(VertexColor()));
  connect(ui_->ScalePlus, SIGNAL(clicked()), this, SLOT(ScaleMul()));
  connect(ui_->ScaleMinus, SIGNAL(clicked()), this, SLOT(ScaleDiv()));
  connect(ui_->LWMinus, SIGNAL(clicked()), this, SLOT(LWidthMinus()));
  connect(ui_->VWMinus, SIGNAL(clicked()), this, SLOT(VWidthMinus()));
  connect(ui_->VertexNo, SIGNAL(clicked()), this, SLOT(VertexType()));
  connect(ui_->StippleNo, SIGNAL(clicked()), this, SLOT(StippleType()));
  connect(ui_->StippleYes, SIGNAL(clicked()), this, SLOT(StippleType()));
  connect(ui_->Central, SIGNAL(clicked()), this, SLOT(ProjectionType()));
  connect(ui_->VertexCircle, SIGNAL(clicked()), this, SLOT(VertexType()));
  connect(ui_->VertexSquare, SIGNAL(clicked()), this, SLOT(VertexType()));
  connect(ui_->Parallel, SIGNAL(clicked()), this, SLOT(ProjectionType()));
  connect(ui_->Screen, SIGNAL(clicked()), this, SLOT(CreateScreenshot()));
  connect(ui_->OXRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateX(int)));
  connect(ui_->OYRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateY(int)));
  connect(ui_->OZRotate, SIGNAL(valueChanged(int)), this, SLOT(RotateZ(int)));
}

void Viewer::SaveSettings() noexcept {
  settings_->setValue("saved", 1);
  settings_->setValue("line_width", l_width_);
  settings_->setValue("vertex_width", v_width_);
  settings_->setValue("scale", ui_->ScaleValue->text());
  settings_->setValue("move_ox", ui_->XMoveValue->text());
  settings_->setValue("move_oy", ui_->YMoveValue->text());
  settings_->setValue("move_oz", ui_->ZMoveValue->text());
  settings_->setValue("color_line_r", color_line_.redF());
  settings_->setValue("color_line_g", color_line_.greenF());
  settings_->setValue("color_line_b", color_line_.blueF());
  settings_->setValue("color_main_r", color_main_.redF());
  settings_->setValue("color_main_g", color_main_.greenF());
  settings_->setValue("color_main_b", color_main_.blueF());
  settings_->setValue("color_main_a", color_main_.alphaF());
  settings_->setValue("color_vertex_r", color_vertex_.redF());
  settings_->setValue("color_vertex_g", color_vertex_.greenF());
  settings_->setValue("color_vertex_b", color_vertex_.blueF());
  settings_->setValue("central_prj", ui_->Central->isChecked());
  settings_->setValue("parallel_prj", ui_->Parallel->isChecked());
  settings_->setValue("vertex_no", ui_->VertexNo->isChecked());
  settings_->setValue("vertex_circle", ui_->VertexCircle->isChecked());
  settings_->setValue("vertex_square", ui_->VertexSquare->isChecked());
  settings_->setValue("line_stipple_no", ui_->StippleNo->isChecked());
  settings_->setValue("line_stipple_yes", ui_->StippleYes->isChecked());
}

void Viewer::LoadSettings() noexcept {
  double r = settings_->value("color_main_r").toDouble();
  double g = settings_->value("color_main_g").toDouble();
  double b = settings_->value("color_main_b").toDouble();
  color_main_ = QColor::fromRgbF(r, g, b);
  r = settings_->value("color_line_r").toDouble();
  g = settings_->value("color_line_g").toDouble();
  b = settings_->value("color_line_b").toDouble();
  color_line_ = QColor::fromRgbF(r, g, b);
  r = settings_->value("color_vertex_r").toDouble();
  g = settings_->value("color_vertex_g").toDouble();
  b = settings_->value("color_vertex_b").toDouble();
  color_vertex_ = QColor::fromRgbF(r, g, b);

  l_width_ = settings_->value("line_width").toDouble();
  v_width_ = settings_->value("vertex_width").toDouble();
  ui_->VertexNo->setChecked(settings_->value("vertex_no", true).toBool());
  ui_->Central->setChecked(settings_->value("central_prj", true).toBool());
  ui_->Parallel->setChecked(settings_->value("parallel_prj", true).toBool());
  ui_->StippleNo->setChecked(settings_->value("line_stipple_no", true).toBool());
  ui_->VertexCircle->setChecked(settings_->value("vertex_circle", true).toBool());
  ui_->VertexSquare->setChecked(settings_->value("vertex_square", true).toBool());
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

void Viewer::OpenFile() {
  QString path = QFileDialog::getOpenFileName(nullptr, "Open File", QString(), "Obj Files (*.obj)");
  if (!path.isEmpty()) {
    ui_->OXRotate->setValue(0);
    ui_->OYRotate->setValue(0);
    ui_->OZRotate->setValue(0);
    ui_->degX->setText("0");
    ui_->degY->setText("0");
    ui_->degZ->setText("0");
    Data &data = ui_->OGL->get_data();
    controller_->Parse(path.toStdString());
    ui_->FileName->setText(path.section('/', -1));
    ui_->VCount->setText(QString::number(data.v_count));
    ui_->ECount->setText(QString::number(data.e_count));
    ui_->OGL->Update();
  }
}

void Viewer::MoveXL() noexcept {
  if (!ui_->XMoveValue->text().isEmpty()) {
    controller_->Move(-ui_->XMoveValue->text().toDouble(), kMoveX);
    ui_->OGL->Update();
  }
}

void Viewer::MoveXR() noexcept {
  if (!ui_->XMoveValue->text().isEmpty()) {
    controller_->Move(ui_->XMoveValue->text().toDouble(), kMoveX);
    ui_->OGL->Update();
  }
}

void Viewer::MoveYD() noexcept {
  if (!ui_->YMoveValue->text().isEmpty()) {
    controller_->Move(-ui_->YMoveValue->text().toDouble(), kMoveY);
    ui_->OGL->Update();
  }
}

void Viewer::MoveYU() noexcept {
  if (!ui_->YMoveValue->text().isEmpty()) {
    controller_->Move(ui_->YMoveValue->text().toDouble(), kMoveY);
    ui_->OGL->Update();
  }
}

void Viewer::MoveZC() noexcept {
  if (!ui_->ZMoveValue->text().isEmpty()) {
    controller_->Move(-ui_->ZMoveValue->text().toDouble(), kMoveZ);
    ui_->OGL->Update();
  }
}

void Viewer::MoveZF() noexcept {
  if (!ui_->ZMoveValue->text().isEmpty()) {
    controller_->Move(ui_->ZMoveValue->text().toDouble(), kMoveZ);
    ui_->OGL->Update();
  }
}

void Viewer::ScaleMul() noexcept {
  if (!ui_->ScaleValue->text().isEmpty()) {
    controller_->Scale(ui_->ScaleValue->text().toDouble(), kScaleP);
    ui_->OGL->Update();
  }
}

void Viewer::ScaleDiv() noexcept {
  if (!ui_->ScaleValue->text().isEmpty()) {
    controller_->Scale(ui_->ScaleValue->text().toDouble(), kScaleM);
    ui_->OGL->Update();
  }
}

void Viewer::RotateX(const int &value) noexcept {
  if (value > check_x_) {
    controller_->Rotate(1, kRotX);
    deg_x_++;
  } else {
    controller_->Rotate(-1, kRotX);
    deg_x_--;
  }
  ui_->degX->setText(QString::number(deg_x_));
  check_x_ = value;
  ui_->OGL->Update();
}

void Viewer::RotateY(const int &value) noexcept {
  if (value > check_y_) {
    controller_->Rotate(1, kRotY);
    deg_y_++;
  } else {
    controller_->Rotate(-1, kRotY);
    deg_y_--;
  }
  ui_->degY->setText(QString::number(deg_y_));
  check_y_ = value;
  ui_->OGL->Update();
}

void Viewer::RotateZ(const int &value) noexcept {
  if (value > check_z_) {
    controller_->Rotate(-1, kRotZ);
    deg_z_++;
  } else {
    controller_->Rotate(1, kRotZ);
    deg_z_--;
  }
  ui_->degZ->setText(QString::number(deg_z_));
  check_z_ = value;
  ui_->OGL->Update();
}

void Viewer::ProjectionType() noexcept {
  if (ui_->Parallel->isChecked())
    ui_->OGL->set_parallel(true);
  else
    ui_->OGL->set_parallel(false);
  ui_->OGL->Update();
}

void Viewer::LWidthPlus() noexcept {
  l_width_ += 0.5;
  ui_->OGL->set_line_width(l_width_);
  ui_->OGL->Update();
}

void Viewer::LWidthMinus() noexcept {
  if (l_width_ > 1) l_width_ -= 0.5;
  ui_->OGL->set_line_width(l_width_);
  ui_->OGL->Update();
}

void Viewer::VWidthPlus() noexcept {
  v_width_ += 0.5;
  ui_->OGL->set_vertex_width(v_width_);
  ui_->OGL->Update();
}

void Viewer::VWidthMinus() noexcept {
  if (v_width_ > 1) v_width_ -= 0.5;
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
  if (ui_->VertexNo->isChecked()) {
    ui_->OGL->set_is_no_vertex(true);
    ui_->OGL->set_is_circle_vertex(false);
  } else if (ui_->VertexCircle->isChecked()) {
    ui_->OGL->set_is_no_vertex(false);
    ui_->OGL->set_is_circle_vertex(true);
  } else {
    ui_->OGL->set_is_no_vertex(false);
    ui_->OGL->set_is_circle_vertex(false);
  }
  ui_->OGL->Update();
}

void Viewer::LineColor() noexcept {
  color_line_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_line_.isValid()) ui_->OGL->set_line_color(color_line_);
  ui_->OGL->Update();
}

void Viewer::VertexColor() noexcept {
  color_vertex_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_vertex_.isValid()) ui_->OGL->set_vertex_color(color_vertex_);
  ui_->OGL->Update();
}

void Viewer::MainColor() noexcept {
  color_main_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_main_.isValid()) ui_->OGL->set_main_color(color_main_);
  ui_->OGL->Update();
}

void Viewer::CreateScreenshot() noexcept {
  QString f_name = QFileDialog::getSaveFileName(this, "Save screenshot", "", "BMP Image (*.bmp);; JPEG Image (*.jpeg)");
  QImage img = ui_->OGL->GetFrame();
  img.save(f_name);
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
  QImage img = ui_->OGL->GetFrame();
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

}  // namespace s21

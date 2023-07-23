#include "viewer.h"
#include "ui_viewer.h"

ViewerWin::ViewerWin(QWidget *parent) : QWidget(parent), ui_(new Ui::ViewerWin) {
  ui_->setupUi(this);
  ogl_ = new OpenGL;
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 1400) / 2;
  int y = (screenGeometry.height() - 600) / 2;
  move(x, y);
  this->setFixedSize(1150, 600);

  connect(ui_->File, SIGNAL(clicked()), this, SLOT(OpenFile()));
  connect(ui_->Panel, SIGNAL(clicked()), this, SLOT(ShowPanel()));
}

ViewerWin::~ViewerWin() {
  delete ogl_;
  delete ui_;
}

void ViewerWin::OpenFile() const noexcept {
    QString f_name_qstr_ = QFileDialog::getOpenFileName(nullptr, "Open File", QString(), "Obj Files (*.obj)");
    ui_->file_name->setText(f_name_qstr_);
    if (f_name_qstr_ != "") {
        ogl_->OpenFile(f_name_qstr_.toStdString());
    }
}

void ViewerWin::ShowPanel() noexcept {
  if (ui_->Panel->text() == '>') {
    this->setFixedSize(1400, 600);
    ui_->Panel->setText("<");
  } else {
    this->setFixedSize(1150, 600);
    ui_->Panel->setText(">");
  }
}

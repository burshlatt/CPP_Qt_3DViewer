#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
    ui_->setupUi(this);
    this->setFixedSize(1400, 600);

    QScreen *screen_ = QGuiApplication::primaryScreen();
    QRect screen_geometry_ = screen_->geometry();
    int x_ = (screen_geometry_.width() - 1400) / 2;
    int y_ = (screen_geometry_.height() - 600) / 2;
    move(x_, y_);

    connect(ui_->Open, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(ui_->button, SIGNAL(clicked()), this, SLOT(MoveX()));
}

Viewer::~Viewer() {
  delete ui_;
}

void Viewer::OpenFile() const noexcept {
    QString path_ = QFileDialog::getOpenFileName(nullptr, "Open File", QString(), "Obj Files (*.obj)");
    if (!path_.isEmpty()) {
        ui_->FileName->setText(path_);
        ui_->OGL->OpenFile(path_.toStdString());
    }
}

void Viewer::MoveX() noexcept {
    if (!ui_->value->text().isEmpty()) {
        ui_->OGL->MoveX(ui_->value->text().toDouble());
    }
}

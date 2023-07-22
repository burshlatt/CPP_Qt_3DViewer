#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  myogl = new MyOpenGL;
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 1400) / 2;
  int y = (screenGeometry.height() - 600) / 2;
  move(x, y);
  this->setFixedSize(1150, 600);
}

Widget::~Widget() {
  delete myogl;
  delete ui;
}

void Widget::on_openFile_clicked() {
  QString f_name_qstr = QFileDialog::getOpenFileName(nullptr, "Открыть файл", QString(), "Объектный файлы (*.obj)");
  if (f_name_qstr != "") {
    ui->file_name->setText(f_name_qstr);
    model_.Parser(f_name_qstr.toStdString());
    myogl->set_f_array(model_.get_facet());
    myogl->set_v_array(model_.get_vertex());
    myogl->set_f_count(model_.get_count_f());
    myogl->set_v_count(model_.get_count_v());
    myogl->set_max_coord(model_.get_max_coord());
//    myogl->check(model_.get_facet(), model_.get_vertex());
  }
}

void Widget::on_show_panel_clicked() {
  if (ui->show_panel->text() == '>') {
    this->setFixedSize(1400, 600);
    ui->show_panel->setText("<");
  } else {
    this->setFixedSize(1150, 600);
    ui->show_panel->setText(">");
  }
}

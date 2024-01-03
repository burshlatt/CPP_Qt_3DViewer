#include <QApplication>
#include <QIcon>

#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/3dviewer.png"));
  s21::Viewer viewer;
  viewer.show();
  return app.exec();
}

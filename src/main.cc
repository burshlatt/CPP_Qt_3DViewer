#include <QApplication>
#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ViewerWin viewer_;
  viewer_.show();
  return a.exec();
}

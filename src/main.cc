#include <QApplication>

#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication apl(argc, argv);
  s21::Viewer viewer;
  viewer.show();
  return apl.exec();
}

#include <QApplication>

#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication apl_(argc, argv);
  s21::Viewer viewer_;
  viewer_.show();
  return apl_.exec();
}

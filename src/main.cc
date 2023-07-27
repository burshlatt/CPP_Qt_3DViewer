#include <QApplication>
#include "view/viewer.h"

int main(int argc, char *argv[]) {
  QApplication apl_(argc, argv);
  Viewer viewer_;
  viewer_.show();
  return apl_.exec();
}

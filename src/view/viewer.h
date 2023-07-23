#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QScreen>
#include <QFileDialog>

#include "opengl.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewerWin;
}
QT_END_NAMESPACE

class ViewerWin : public QWidget {
  Q_OBJECT

    public:
        ViewerWin(QWidget *parent = nullptr);
        ~ViewerWin();

    public slots:
        void ShowPanel() noexcept;
        void OpenFile() const noexcept;

    private:
        OpenGL *ogl_;
        Ui::ViewerWin *ui_;
};

#endif  // VIEWER_H

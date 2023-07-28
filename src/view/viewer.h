#ifndef VIEWER_H
#define VIEWER_H

#include <QScreen>
#include <QFileDialog>
#include <QMainWindow>

#include "opengl.h"

namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow {
    Q_OBJECT

    public:
        explicit Viewer(QWidget *parent = nullptr);
        ~Viewer();

    public slots:
        void OpenFile() const noexcept;
        void MoveX() noexcept;

    private:
        Ui::Viewer *ui_;
};

#endif // VIEWER_H

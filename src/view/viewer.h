#ifndef VIEWER_H
#define VIEWER_H

#include <QColor>
#include <QScreen>
#include <QFileDialog>
#include <QMainWindow>
#include <QColorDialog>

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
        void OpenFile() noexcept;
        void MoveXL() noexcept;
        void MoveXR() noexcept;
        void MoveYD() noexcept;
        void MoveYU() noexcept;
        void MoveZC() noexcept;
        void MoveZF() noexcept;
        void RotateX() noexcept;
        void RotateY() noexcept;
        void RotateZ() noexcept;
        void ScaleMul() noexcept;
        void ScaleDiv() noexcept;
        void StippleNo() noexcept;
        void StippleYes() noexcept;
        void LineColor() noexcept;
        void VertexNo() noexcept;
        void VertexCircle() noexcept;
        void VertexSquare() noexcept;
        void VertexColor() noexcept;
        void LWidthPlus() noexcept;
        void LWidthMinus() noexcept;
        void VWidthPlus() noexcept;
        void VWidthMinus() noexcept;
        void CentralPrj() noexcept;
        void ParallelPrj() noexcept;

    private:
        Data data_;
        Ui::Viewer *ui_;
        s21::Parser parser_;
        double l_width_ = 1.0;
        double v_width_ = 1.0;
};

#endif // VIEWER_H

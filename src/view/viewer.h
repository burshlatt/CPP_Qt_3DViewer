#ifndef VIEWER_H
#define VIEWER_H

#include <QColor>
#include <QScreen>
#include <QSettings>
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
        void CreateGIF() noexcept;
        void CreateScreenshot() noexcept;

        void OpenFile() noexcept;
        void SaveSettings() noexcept;
        void LoadSettings() noexcept;
        void MoveXL() noexcept;
        void MoveXR() noexcept;
        void MoveYD() noexcept;
        void MoveYU() noexcept;
        void MoveZC() noexcept;
        void MoveZF() noexcept;
        void RotateX(const int &value) noexcept;
        void RotateY(const int &value) noexcept;
        void RotateZ(const int &value) noexcept;
        void ScaleMul() noexcept;
        void ScaleDiv() noexcept;
        void StippleType() noexcept;
        void LineColor() noexcept;
        void MainColor() noexcept;
        void VertexType() noexcept;
        void VertexColor() noexcept;
        void LWidthPlus() noexcept;
        void LWidthMinus() noexcept;
        void VWidthPlus() noexcept;
        void VWidthMinus() noexcept;
        void ProjectionType() noexcept;

    private:
        Ui::Viewer *ui_;
        s21::Parser parser_;

        Data data_;
        QColor color_main_ = Qt::black;
        QColor color_line_ = Qt::white;
        QColor color_vertex_ = Qt::white;
        QSettings *settings_;
        int check_x_ = 50;
        int check_y_ = 50;
        int check_z_ = 50;
        double l_width_ = 1.0;
        double v_width_ = 1.0;
};

#endif // VIEWER_H

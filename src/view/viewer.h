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
        void SaveGIF() noexcept;
        void CreateGIF() noexcept;
        void CreateScreenshot() noexcept;

        void MoveXL() noexcept;
        void MoveXR() noexcept;
        void MoveYD() noexcept;
        void MoveYU() noexcept;
        void MoveZC() noexcept;
        void MoveZF() noexcept;
        void OpenFile() noexcept;
        void ScaleMul() noexcept;
        void ScaleDiv() noexcept;
        void LineColor() noexcept;
        void MainColor() noexcept;
        void VertexType() noexcept;
        void LWidthPlus() noexcept;
        void VWidthPlus() noexcept;
        void LWidthMinus() noexcept;
        void VWidthMinus() noexcept;
        void VertexColor() noexcept;
        void StippleType() noexcept;
        void SaveSettings() noexcept;
        void LoadSettings() noexcept;
        void ProjectionType() noexcept;
        void RotateX(const int &value) noexcept;
        void RotateY(const int &value) noexcept;
        void RotateZ(const int &value) noexcept;

    private:
        Ui::Viewer *ui_;
        s21::Parser parser_;

        QTimer *timer_;
        QGifImage *frame_;
        QString gif_name_;
        int frame_count_ = 0;

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

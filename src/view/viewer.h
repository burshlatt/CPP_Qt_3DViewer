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

        void CreateGIF() noexcept;
        void Connections() noexcept;
        void CreateScreenshot() noexcept;

    public slots:
        void MoveXL() noexcept;
        void MoveXR() noexcept;
        void MoveYD() noexcept;
        void MoveYU() noexcept;
        void MoveZC() noexcept;
        void MoveZF() noexcept;
        void SaveGIF() noexcept;
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
        Data data_;
        Ui::Viewer *ui_;
        s21::Parser parser_;

        QTimer *timer_;
        QGifImage *frame_;
        QString gif_name_;

        int check_x_;
        int check_y_;
        int check_z_;
        double l_width_;
        double v_width_;
        int frame_count_;

        QColor color_main_;
        QColor color_line_;
        QColor color_vertex_;
        QSettings *settings_;
};

#endif // VIEWER_H

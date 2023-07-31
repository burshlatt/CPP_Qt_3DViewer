#ifndef OPENGL_H
#define OPENGL_H

#include <QTimer>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "qgifimage.h"
#include "../model/parser.h"
#include "../model/affine.h"

class OpenGL : public QOpenGLWidget {
  Q_OBJECT

    public:
        OpenGL(QWidget *parent = nullptr);
        ~OpenGL();

        void set_data(const Data &data) noexcept;
        void set_stipple(const bool &is_stipple) noexcept;
        void set_main_color(const QColor &color) noexcept;
        void set_line_color(const QColor &color) noexcept;
        void set_vertex_color(const QColor &color) noexcept;
        void set_parallel(const bool &is_parallel) noexcept;
        void set_line_width(const double &width) noexcept;
        void set_vertex_width(const double &width) noexcept;
        void set_vertex_type(const bool &no, const bool &circle) noexcept;

        void Timer() noexcept;
        void SaveGIF() noexcept;
        void CreateGIF() noexcept;
        void CreateScreenshot() noexcept;
        void ShowMessage(QString message) noexcept;

        void Draw() noexcept;
        void Update() noexcept;
        void paintGL() override;
        void Perspective() noexcept;
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void ScaleMul(const double &value) noexcept;
        void ScaleDiv(const double &value) noexcept;
        void Move(const double &value, const int &coord) noexcept;
        void Rotate(const double &value, const int &coord) noexcept;

    private:
        QTimer *gifTmr_;
        QGifImage *gifImg_;
        QString gifFileName_;
        int numberFps_ = 0;

        Data data_;
        s21::Affine affine_;
        bool is_parallel_ = true;
        bool is_stipple_ = false;
        double line_width_ = 0.0;
        double vertex_width_ = 0.0;
        bool is_no_vertex_ = false;
        bool is_circle_vertex_ = false;
        QColor main_color_ = Qt::black;
        QColor line_color_ = Qt::white;
        QColor vertex_color_ = Qt::white;
};

#endif  // OPENGL_H

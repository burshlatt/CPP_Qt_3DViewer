#ifndef OPENGL_H
#define OPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "../model/parser.h"
#include "../model/affine.h"

class OpenGL : public QOpenGLWidget {
  Q_OBJECT

    public:
        OpenGL(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}
        ~OpenGL() {}

        void MoveX(const double &value) noexcept;

        void Draw() noexcept;
        void paintGL() override;
        void Perspective() noexcept;
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void OpenFile(const std::string &path) noexcept;

    private:
        Data data_;
        s21::Parser parser_;
        s21::Affine affine_;
};

#endif  // OPENGL_H

#ifndef OPENGL_H
#define OPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "../model/parser.h"

class OpenGL : public QOpenGLWidget {
  Q_OBJECT

    public:
        OpenGL(QWidget *parent = nullptr);
        ~OpenGL();

        void Draw() noexcept;
        void paintGL() override;
        void Perspective() noexcept;
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void OpenFile(const std::string &path) noexcept;

    private:
        Data *data_;
        s21::Parser *parser_;
        int size_ = 0;
        int v_count_ = 0;
        int *facets_ = nullptr;
        double max_coord_ = 0.0;
        double *vertexes_ = nullptr;
};

#endif  // OPENGL_H

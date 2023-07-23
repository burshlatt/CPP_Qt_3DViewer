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

        void paintGL() override;
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void OpenFile(const std::string &path) noexcept;

    private:
        s21::Parser parser_;
        int f_count_ = 0;
        int v_count_ = 0;
        double max_coord_ = 0.0;
        std::vector<double> v_vec_;
        std::vector<unsigned int> f_vec_;
};

#endif  // OPENGL_H

#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QtOpenGL>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <QOpenGLWidget>
#include "../model/model.h"

class MyOpenGL : public QOpenGLWidget {
  Q_OBJECT

    public:
        MyOpenGL(QWidget *parent = nullptr);

        void set_f_count(const int &count) noexcept;
        void set_v_count(const int &count) noexcept;
        void set_max_coord(const double &cord) noexcept;
        void set_v_array(const std::vector<double> &arr) noexcept;
        void set_f_array(const std::vector<unsigned int> &arr) noexcept;

        void check() noexcept;
        void paintGL() override;
        void initializeGL() override;
        void DrawObject() const noexcept;
        void resizeGL(int w, int h) override;

    private:
        s21::model mode_;
        int f_count_ = 0;
        int v_count_ = 0;
        double max_coord_ = 0.0;
        std::vector<double> v_array_;
        std::vector<unsigned int> f_array_;
};

#endif  // MYOPENGL_H

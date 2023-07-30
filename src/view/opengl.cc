#include "opengl.h"

//void OpenGL::Update() noexcept {
//    update();
//}

void OpenGL::set_data(const Data &data) noexcept {
    data_ = data;
    update();
}

void OpenGL::set_parallel(const bool &is_parallel) noexcept {
    is_parallel_ = is_parallel;
    update();
}

void OpenGL::set_line_color(const QColor &color) noexcept {
    line_color_ = color;
    update();
}

void OpenGL::set_vertex_color(const QColor &color) noexcept {
    vertex_color_ = color;
    update();
}

void OpenGL::set_stipple(const bool &is_stipple) noexcept {
    is_stipple_ = is_stipple;
    update();
}

void OpenGL::set_line_width(const double &width) noexcept {
    line_width_ = width;
    update();
}

void OpenGL::set_vertex_width(const double &width) noexcept {
    vertex_width_ = width;
    update();
}

void OpenGL::set_vertex_type(const bool &no, const bool &circle) noexcept {
    is_no_vertex_ = no;
    is_circle_vertex_ = circle;
    update();
}

void OpenGL::Move(const double &value, const int &coord) noexcept {
    affine_.Move(data_, value, coord);
    update();
}

void OpenGL::Rotate(const double &value, const int &coord) noexcept {
    affine_.Rotate(data_, value, coord);
    update();
}

void OpenGL::ScaleMul(const double &value) noexcept {
    affine_.ScaleMul(data_, value);
    update();
}

void OpenGL::ScaleDiv(const double &value) noexcept {
    affine_.ScaleDiv(data_, value);
    update();
}

void OpenGL::initializeGL() { glEnable(GL_DEPTH_TEST); }

void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGL::paintGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Perspective();
    Draw();
}

void OpenGL::Perspective() noexcept {
    double max_ = data_.max_coord_ * 1.2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (is_parallel_) {
        glOrtho(-max_, max_, -max_, max_, -max_, (max_ + 10) * 10);
        glTranslated(0, 0, -3);
    } else {
        double value_ = tan(90 / 360 * M_PI) * 0.001;
        glFrustum(-value_, value_, -value_, value_, -max_, (max_ + 10) * 10);
        glTranslatef(0, 0, -max_);
    }
}

void OpenGL::Draw() noexcept {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glVertexPointer(3, GL_DOUBLE, 0, data_.vertexes_.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(line_color_.redF(), line_color_.greenF(), line_color_.blueF());
    glLineWidth(line_width_);
    if (is_stipple_) {
        glLineStipple(5, 0x3333);
        glEnable(GL_LINE_STIPPLE);
    }
    glDrawElements(GL_LINES, data_.facets_.size(), GL_UNSIGNED_INT, data_.facets_.data());
    glColor3d(vertex_color_.redF(), vertex_color_.greenF(), vertex_color_.blueF());
    glPointSize(vertex_width_);

    if (is_circle_vertex_)
        glEnable(GL_POINT_SMOOTH);
    if (!is_no_vertex_)
        glDrawArrays(GL_POINTS, 0, data_.v_count_);
    if (is_circle_vertex_)
        glDisable(GL_POINT_SMOOTH);

    if (is_stipple_)
        glDisable(GL_LINE_STIPPLE);
    glDisableClientState(GL_VERTEX_ARRAY);
}

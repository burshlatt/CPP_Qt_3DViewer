#include "opengl.h"

namespace s21 {
OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    line_width_ = 0.0;
    vertex_width_ = 0.0;
    is_parallel_ = true;
    is_stipple_ = false;
    is_no_vertex_ = false;
    is_circle_vertex_ = false;
    main_color_ = Qt::black;
    line_color_ = Qt::white;
    vertex_color_ = Qt::white;
}

OpenGL::~OpenGL() {
    glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGL::set_data(const Data &data) noexcept { data_ = data; }
void OpenGL::set_is_no_vertex(const bool &no) noexcept { is_no_vertex_ = no; }
void OpenGL::set_main_color(const QColor &color) noexcept { main_color_ = color; }
void OpenGL::set_line_color(const QColor &color) noexcept { line_color_ = color; }
void OpenGL::set_line_width(const double &width) noexcept { line_width_ = width; }
void OpenGL::set_vertex_color(const QColor &color) noexcept { vertex_color_ = color; }
void OpenGL::set_vertex_width(const double &width) noexcept { vertex_width_ = width; }
void OpenGL::set_stipple(const bool &is_stipple) noexcept { is_stipple_ = is_stipple; }
void OpenGL::set_parallel(const bool &is_parallel) noexcept { is_parallel_ = is_parallel; }
void OpenGL::set_is_circle_vertex(const bool &circle) noexcept { is_circle_vertex_ = circle; }

void OpenGL::Update() noexcept { update(); }
QImage OpenGL::GetFrame() noexcept { return grabFramebuffer(); }

void OpenGL::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
}

void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGL::paintGL() {
    glClearColor(main_color_.redF(), main_color_.greenF(), main_color_.blueF(), main_color_.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Perspective();
    Draw();
}

void OpenGL::Perspective() noexcept {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (is_parallel_) {
        glOrtho(-(data_.max_coord_), data_.max_coord_, -(data_.max_coord_), data_.max_coord_, -(data_.far_), data_.far_);
    } else {
        glFrustum(-(data_.max_coord_), data_.max_coord_, -(data_.max_coord_), data_.max_coord_, data_.near_, data_.far_);
        glTranslated(0, 0, -data_.near_ * 3);
    }
}

void OpenGL::Draw() noexcept {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glVertexPointer(3, GL_DOUBLE, 0, data_.vertexes_.data());
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
}
} // namespace s21

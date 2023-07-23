#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGL::OpenFile(const std::string &path) noexcept {
    parser_.Parse(path);
    f_vec_ = parser_.get_facet();
    v_vec_ = parser_.get_vertex();
    f_count_ = parser_.get_count_f();
    v_count_ = parser_.get_count_v();
    max_coord_ = parser_.get_max_coord();
    update();
}

void OpenGL::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGL::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glLoadIdentity();
    glOrtho(-max_coord_, max_coord_, -max_coord_, max_coord_, -max_coord_, (max_coord_ + 5) * 5);
    glTranslated(0, 0, -3);
}

void OpenGL::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(10);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertexPointer(3, GL_DOUBLE, 0, v_vec_.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, v_count_);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(10);
    glDrawElements(GL_LINES, f_vec_.size(), GL_UNSIGNED_INT, f_vec_.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}

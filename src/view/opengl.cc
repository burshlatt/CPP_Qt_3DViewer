#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    parser_ = new s21::Parser;
}

OpenGL::~OpenGL() {
    delete parser_;
    facets_ = nullptr;
    vertexes_ = nullptr;
}

void OpenGL::OpenFile(const std::string &path) noexcept {
    parser_->Parse(path);
    data_ = parser_->get_view();

    v_count_ = data_->v_count_;
    size_ = data_->facets_.size();
    facets_ = data_->facets_.data();
    max_coord_ = data_->max_coord_ * 2;
    vertexes_ = data_->vertexes_.data();

    update();
}

void OpenGL::initializeGL() { glEnable(GL_DEPTH_TEST); }

void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGL::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Perspective();
    Draw();
}

void OpenGL::Perspective() noexcept {
    glOrtho(-max_coord_, max_coord_, -max_coord_, max_coord_, -100, 100);
}

void OpenGL::Draw() noexcept {
    glVertexPointer(3, GL_DOUBLE, 0, vertexes_);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, size_, GL_UNSIGNED_INT, facets_);
    glDrawArrays(GL_POINTS, 0, v_count_);
    glDisableClientState(GL_VERTEX_ARRAY);
}

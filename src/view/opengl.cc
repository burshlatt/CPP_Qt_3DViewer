#include "opengl.h"

void OpenGL::OpenFile(const std::string &path) noexcept {
    parser_.Parse(path);
    data_ = parser_.get_data();
    update();
}

void OpenGL::MoveX(const double &value) noexcept {
    affine_.MoveX(data_, value);
    update();
}

void OpenGL::initializeGL() { glEnable(GL_DEPTH_TEST); }

void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGL::paintGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Perspective();
    Draw();
}

void OpenGL::Perspective() noexcept {
    double max_ = data_.max_coord_ * 2;
    glOrtho(-max_, max_, -max_, max_, -100, 100);
}

void OpenGL::Draw() noexcept {
    glVertexPointer(3, GL_DOUBLE, 0, data_.vertexes_.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, data_.facets_.size(), GL_UNSIGNED_INT, data_.facets_.data());
    glDrawArrays(GL_POINTS, 0, data_.v_count_);
    glDisableClientState(GL_VERTEX_ARRAY);
}

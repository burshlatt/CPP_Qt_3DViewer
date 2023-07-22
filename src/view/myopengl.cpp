#include "myopengl.h"

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent) {}

void MyOpenGL::set_f_count(const int &count) noexcept { f_count_ = count; }
void MyOpenGL::set_v_count(const int &count) noexcept { v_count_ = count; }
void MyOpenGL::set_v_array(const std::vector<double> &arr) noexcept { v_array_ = arr; }
void MyOpenGL::set_f_array(const std::vector<unsigned int> &arr) noexcept { f_array_ = arr; }

void MyOpenGL::check() noexcept {
//    for (size_t i = 0; i < f_array_.size(); i++) {
//        std::cout << f_array_[i] << " ";
//    }
//    for (size_t i = 0; i < v_array_.size(); i++) {
//        std::cout << v_array_[i] << std::endl;
//    }
//    std::cout << f_count_ << std::endl;
//    std::cout << v_count_ << std::endl;
}

void MyOpenGL::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void MyOpenGL::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void MyOpenGL::paintGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

//    float fov = 60.0 * M_PI / 180;
//    float heapHeight = 600 / (2 * tan(fov / 2));
//    glFrustum(-800, 800, -600, 600, heapHeight, 100);

    DrawObject();
}

void MyOpenGL::DrawObject() const noexcept {
    glVertexPointer(3, GL_DOUBLE, 0, v_array_.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1.0, 0.0, 0.0);
    glDrawElements(GL_LINES, static_cast<int>(f_array_.size()), GL_UNSIGNED_INT, f_array_.data());
    glDisableClientState(GL_VERTEX_ARRAY);
//    update();
}

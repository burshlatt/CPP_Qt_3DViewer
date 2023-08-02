#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    timer_ = new QTimer(0);
    connect(timer_, SIGNAL(timeout()), this, SLOT(SaveGIF()));
}

OpenGL::~OpenGL() {
    delete timer_;
}

void OpenGL::set_data(const Data &data) noexcept { data_ = data; }
void OpenGL::set_main_color(const QColor &color) noexcept { main_color_ = color; }
void OpenGL::set_line_color(const QColor &color) noexcept { line_color_ = color; }
void OpenGL::set_line_width(const double &width) noexcept { line_width_ = width; }
void OpenGL::set_vertex_color(const QColor &color) noexcept { vertex_color_ = color; }
void OpenGL::set_vertex_width(const double &width) noexcept { vertex_width_ = width; }
void OpenGL::set_stipple(const bool &is_stipple) noexcept { is_stipple_ = is_stipple; }
void OpenGL::set_parallel(const bool &is_parallel) noexcept { is_parallel_ = is_parallel; }

void OpenGL::set_vertex_type(const bool &no, const bool &circle) noexcept {
    is_no_vertex_ = no;
    is_circle_vertex_ = circle;
    update();
}

void OpenGL::Update() noexcept { update(); }
void OpenGL::ScaleMul(const double &value) noexcept { affine_.ScaleMul(data_, value); }
void OpenGL::ScaleDiv(const double &value) noexcept { affine_.ScaleDiv(data_, value); }
void OpenGL::Move(const double &value, const int &coord) noexcept { affine_.Move(data_, value, coord); }
void OpenGL::Rotate(const double &value, const int &coord) noexcept { affine_.Rotate(data_, value, coord); }

void OpenGL::CreateScreenshot() noexcept {
    QString f_name_ = QFileDialog::getSaveFileName(this, "Save screenshot", "", "BMP Image (*.bmp);; JPEG Image (*.jpeg)");
    QImage img_ = grabFramebuffer();
    img_.save(f_name_);
}

void OpenGL::CreateGIF() noexcept {
  gif_name_ = QFileDialog::getSaveFileName(this, "Save GIF", ".gif", "Gif Files (*.gif)");
  if (gif_name_ != "") {
    frame_ = new QGifImage;
    frame_->setDefaultDelay(10);
    timer_->setInterval(100);
    timer_->start();
  }
}

void OpenGL::SaveGIF() noexcept {
  QImage image_ = grabFramebuffer();
  frame_->addFrame(image_);
  if (frame_count_ == 50) {
    timer_->stop();
    frame_->save(gif_name_);
    frame_count_ = 0;
    delete frame_;
  }
  frame_count_++;
}

void OpenGL::initializeGL() { glEnable(GL_DEPTH_TEST); }
void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGL::paintGL() {
    glClearColor(main_color_.redF(), main_color_.greenF(), main_color_.blueF(), main_color_.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Perspective();
    Draw();
}

void OpenGL::Perspective() noexcept {
    double max_ = data_.max_coord_ * 1.2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (is_parallel_) {
        glOrtho(-max_, max_, -max_, max_, -((max_ + 10) * 10), (max_ + 10) * 10);
    } else {
        float heap_height_ = max_ / (2 * tan(60.0 * M_PI / 180 / 2));
        glFrustum(-max_, max_, -max_, max_, heap_height_, (max_ + 10) * 10);
        glTranslated(0, 0, -heap_height_ * 3);
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

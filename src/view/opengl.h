#ifndef OPENGL_H
#define OPENGL_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

#include "../model/struct.h"
#include "qgifimage.h"

namespace s21 {
class OpenGL : public QOpenGLWidget {
  Q_OBJECT

 public:
  OpenGL(QWidget *parent = nullptr);
  ~OpenGL();

  void set_data(const Data &data) noexcept;
  void set_is_no_vertex(const bool &no) noexcept;
  void set_stipple(const bool &is_stipple) noexcept;
  void set_main_color(const QColor &color) noexcept;
  void set_line_color(const QColor &color) noexcept;
  void set_line_width(const double &width) noexcept;
  void set_vertex_color(const QColor &color) noexcept;
  void set_parallel(const bool &is_parallel) noexcept;
  void set_vertex_width(const double &width) noexcept;
  void set_is_circle_vertex(const bool &circle) noexcept;

  QImage GetFrame() noexcept;

  void Draw() noexcept;
  void Update() noexcept;
  void paintGL() override;
  void Perspective() noexcept;
  void initializeGL() override;
  void resizeGL(int w, int h) override;

 private:
  Data data_;
  double line_width_, vertex_width_;
  QColor main_color_, line_color_, vertex_color_;
  bool is_stipple_, is_parallel_, is_no_vertex_, is_circle_vertex_;
};
}  // namespace s21

#endif  // OPENGL_H

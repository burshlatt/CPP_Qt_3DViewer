#ifndef CPP_QT_3DVIEWER_VIEW_OPENGL_H
#define CPP_QT_3DVIEWER_VIEW_OPENGL_H

#include <QImage>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QPainter>
#include <QVector3D>

#include "../lib/struct.h"

namespace s21 {
typedef struct {
  double scale_value;
  GLfloat line_size;
  GLfloat vertex_size;
  QColor main_color;
  QVector3D line_color;
  QVector3D vertex_color;
  VType vertex_type;
  SType shading_type;
  ModelType model_type;
  Projection projection_type;
} Options;

class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

    public:
        explicit OpenGL(QWidget *parent = nullptr);
        OpenGL(OpenGL &&other) = delete;
        OpenGL(const OpenGL &other) = delete;
        ~OpenGL() override;

        Data &get_data() noexcept;
        Options &get_opt() noexcept;
        QImage get_frame() noexcept;

        void set_vertex_type(VType type);
        void set_line_size(GLfloat size);
        void set_shading_type(SType type);
        void set_main_color(QColor color);
        void set_vertex_size(GLfloat size);
        void set_model_type(ModelType type);
        void set_projection(Projection prj);
        void set_line_color(QVector3D color);
        void set_vertex_color(QVector3D color);

        void Start();
        void ClearBuff();
        void AddShaders();
        void SetTextures();
        void ProgramCreate();
        void ApplySettings();
        void ClearTransformations();
        void Rotate(int value, Coord coord);
        void Move(double value, Coord coord);
        void Scale(double value, ScaleAct act);
        void LoadTexture(QOpenGLTexture &texture, std::string_view path);
        void ResetTexture(int index_mtl, MapType map_type, const QString &path = "");
        void SaveUvMap(unsigned int index_mtl, const std::string &path_texture, const QString &path_save);

        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;

        void wheelEvent(QWheelEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;

    private:
        struct Maps {
            QOpenGLTexture ambient;
            QOpenGLTexture diffuse;
            QOpenGLTexture specular;
            Maps();
            ~Maps() = default;
        };

        Data data_;
        Options opt_;

        QOpenGLBuffer vbo_;
        QOpenGLBuffer ebo_;
        QOpenGLVertexArrayObject vao_;
        QOpenGLShaderProgram *program_;

        GLint uniforms_[11]{};
        QPoint last_mouse_pos_;
        QVector3D moves_{};
        QVector3D angles_{};
        QMatrix4x4 move_mat_;
        QMatrix4x4 scale_mat_;
        QMatrix4x4 rotate_mat_;
        QMatrix4x4 ortho_mat_;
        QMatrix4x4 perspective_mat_;
        std::unique_ptr<Maps[]> maps_{};
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_VIEW_OPENGL_H

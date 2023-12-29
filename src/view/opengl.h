#ifndef CPP_QT_3DVIEWER_VIEW_OPENGL_H
#define CPP_QT_3DVIEWER_VIEW_OPENGL_H

#include <QPainter>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QVector3D>
#include <QImage>

#include <memory>

#include "../lib/parser.h"
#include "../lib/struct.h"

namespace s21 {
class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:    
    explicit OpenGL(QWidget *parent = nullptr);
    ~OpenGL() override;

    const Data& get_data() const noexcept;

    void set_model_type(ModelType type);
    void set_projection(Projection prj);
    void set_vertex_type(VType type) noexcept;
    void set_line_size(GLfloat size) noexcept;
    void set_shading_type(SType type) noexcept;
    void set_main_color(QColor color) noexcept;
    void set_vertex_size(GLfloat size) noexcept;
    void set_line_color(QVector3D color) noexcept;
    void set_vertex_color(QVector3D color) noexcept;

    void ClearBuff();
    void AddShaders();
    void SetTextures();
    void ProgramCreate();
    void ClearTransformations();
    void Rotate(int value, Coord coord);
    void Move(double value, Coord coord);
    void Scale(double value, ScaleAct act);
    void Open(std::string_view path) noexcept;
    void LoadTexture(QOpenGLTexture& texture, std::string_view path);
    void ResetTexture(int index_mtl, MapType map_type, const QString& path = "");
    void SaveUvMap(unsigned int index_mtl, const std::string& path_texture, const QString& path_save);

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    typedef struct {
        VType vertex_type;
        SType shading_type;
        ModelType model_type;
        Projection projection_type;
        GLfloat line_size;
        GLfloat vertex_size;
        QColor main_color;
        QVector3D line_color;
        QVector3D vertex_color;
        double scale_value;
    } Options;

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

    std::unique_ptr<Parser> parser_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_VIEW_OPENGL_H

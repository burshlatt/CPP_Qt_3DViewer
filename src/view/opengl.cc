#include "opengl.h"

#include <iostream>

namespace s21 {
OpenGL::OpenGL(QWidget *parent) :
            QOpenGLWidget(parent),
            vbo_(QOpenGLBuffer::VertexBuffer),
            ebo_(QOpenGLBuffer::IndexBuffer) {

    parser_ = std::make_unique<Parser>(data_);

    opt_.line_size = 1.0f;
    opt_.scale_value = 1.0;
    opt_.vertex_size = 1.0f;
    opt_.model_type = kFrame;
    opt_.vertex_type = kNone;
    opt_.shading_type = kSmooth;
    opt_.main_color = "#686868";
    opt_.projection_type = kParallel;
    opt_.line_color = { 1.0f, 1.0f, 1.0f };
    opt_.vertex_color = { 1.0f, 1.0f, 1.0f };
}

OpenGL::~OpenGL() {
    ClearBuff();
    ClearTransformations();
}

const Data& OpenGL::get_data() const noexcept { return data_; }

OpenGL::Maps::Maps() :
        ambient(QOpenGLTexture::Target2D),
        diffuse(QOpenGLTexture::Target2D),
        specular(QOpenGLTexture::Target2D) {}

void OpenGL::set_main_color(QColor color) noexcept {
    opt_.main_color = color;
    update();
}

void OpenGL::set_line_color(QVector3D color) noexcept {
    opt_.line_color = color;
    update();
}

void OpenGL::set_vertex_color(QVector3D color) noexcept {
    opt_.vertex_color = color;
    update();
}

void OpenGL::set_vertex_type(VType type) noexcept {
    opt_.vertex_type = type;
    update();
}

void OpenGL::set_line_size(GLfloat size) noexcept {
    opt_.line_size = size;
    update();
}

void OpenGL::set_vertex_size(GLfloat size) noexcept {
    opt_.vertex_size = size;
    update();
}

void OpenGL::set_shading_type(SType type) noexcept {
    opt_.shading_type = type;
    ClearBuff();
    ProgramCreate();
    resizeGL(width(), height());
    update();
}

void OpenGL::set_projection(Projection prj) {
    opt_.projection_type = prj;
    resizeGL(width(), height());
    update();
}

void OpenGL::set_model_type(ModelType type) {
    opt_.model_type = type;
    ClearBuff();
    ProgramCreate();
    resizeGL(width(), height());
    update();
}

void OpenGL::ClearBuff() {
    makeCurrent();
    vao_.destroy();
    vbo_.destroy();
    ebo_.destroy();
    program_->deleteLater();
}

void OpenGL::ClearTransformations() {
    moves_ = QVector3D();
    angles_ = QVector3D();
    opt_.scale_value = 1.0f;
    move_mat_.setToIdentity();
    scale_mat_.setToIdentity();
    rotate_mat_.setToIdentity();
}

void OpenGL::Open(std::string_view path) noexcept {
    ClearBuff();
    ClearTransformations();
    parser_->Parse(path);
//    data_ = parser_->get_data();
    ProgramCreate();
    SetTextures();
    resizeGL(width(), height());
    update();
}

void OpenGL::LoadTexture(QOpenGLTexture& texture, std::string_view path) {
    texture.destroy();
    QImage tex_image;
    if (!path.empty())
        tex_image.load(path.data());

    if (tex_image.isNull()) {
        QImage image(1, 1, QImage::Format_RGB32);
        image.fill(QColor::fromRgbF(0.7f, 0.7f, 0.7f));
        tex_image = std::move(image);
    }
    texture.setData(tex_image.mirrored());
    texture.setMinificationFilter(QOpenGLTexture::Nearest);
    texture.setMagnificationFilter(QOpenGLTexture::Linear);
    texture.setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGL::SetTextures() {
    maps_ = std::make_unique<Maps[]>(data_.mtl.size());
    for (size_t i = 0; i < data_.mtl.size(); ++i) {
        LoadTexture(maps_[i].ambient, data_.mtl[i].map_ka);
        LoadTexture(maps_[i].diffuse, data_.mtl[i].map_kd);
        LoadTexture(maps_[i].specular, data_.mtl[i].map_ks);
    }
}

void OpenGL::ResetTexture(int index_mtl, MapType map_type, const QString& path) {
    if (map_type == kAmbient)
        LoadTexture(maps_[index_mtl].ambient, path.toStdString());
    else if (map_type == kDiffuse)
        LoadTexture(maps_[index_mtl].diffuse, path.toStdString());
    else if (map_type == kSpecular)
        LoadTexture(maps_[index_mtl].specular, path.toStdString());
    update();
}

void OpenGL::SaveUvMap(unsigned int index_mtl, const std::string& path_texture, const QString& path_save) {
    unsigned int prev_off = 0;
    for (auto& umtl : data_.usemtl) {
        if (umtl.index == index_mtl) {
            auto img = QImage(path_texture.data()).mirrored();
            QPainter painter(&img);
            for (; prev_off < umtl.offset_uv; prev_off += 2) {
                unsigned int ft1 = data_.uv_map[prev_off] * 2;
                unsigned int ft2 = data_.uv_map[prev_off + 1] * 2;
                qreal vx1 = data_.vertexes_t[ft1] * img.width();
                qreal vy1 = data_.vertexes_t[ft1 + 1] * img.height();
                qreal vx2 = data_.vertexes_t[ft2] * img.width();
                qreal vy2 = data_.vertexes_t[ft2 + 1] * img.height();
                QLineF line(vx1, vy1, vx2, vy2);
                painter.drawLine(line);
            }
            img.mirrored().save(path_save);
            break;
        }
        prev_off = umtl.offset_uv;
    }
}

void OpenGL::Rotate(int value, Coord coord) {
    rotate_mat_.setToIdentity();
    angles_[coord] += value;
    angles_[coord] = fmod(angles_[coord], 360.0);
    rotate_mat_.rotate(angles_.x(), 1.0f, 0.0f, 0.0f);
    rotate_mat_.rotate(angles_.y(), 0.0f, 1.0f, 0.0f);
    rotate_mat_.rotate(angles_.z(), 0.0f, 0.0f, 1.0f);
    update();
}

void OpenGL::Move(double value, Coord coord) {
    moves_[coord] += value;
    move_mat_.setToIdentity();
    move_mat_.translate(moves_.x(), 0.0f, 0.0f);
    move_mat_.translate(0.0f, moves_.y(), 0.0f);
    move_mat_.translate(0.0f, 0.0f, moves_.z());
    update();
}

void OpenGL::Scale(double value, ScaleAct act) {
    scale_mat_.setToIdentity();
    if (act == kScaleMul)
        opt_.scale_value *= value;
    else
        opt_.scale_value /= value;
    scale_mat_.scale(opt_.scale_value);
    update();
}

void OpenGL::AddShaders() {
    QString vertex_path;
    QString fragment_path;
    if (opt_.model_type == kFrame) {
        vertex_path = ":/shaders/wireframe_vertex.glsl";
        fragment_path = ":/shaders/wireframe_fragment.glsl";
    } else if (opt_.model_type == kDashed) {
        vertex_path = ":/shaders/wireframe_dashed_vertex.glsl";
        fragment_path = ":/shaders/wireframe_dashed_fragment.glsl";
    } else if (opt_.model_type == kSolid && data_.is_normals) {
        vertex_path = ":/shaders/solid_vertex.glsl";
        if (opt_.shading_type == kSmooth)
            fragment_path = ":/shaders/solid_fragment.glsl";
        else if (opt_.shading_type == kFlat)
            fragment_path = ":/shaders/solid_flat_fragment.glsl";
    } else if (opt_.model_type == kTextured && data_.is_normals) {
        if (opt_.shading_type == kSmooth) {
            vertex_path = ":/shaders/texture_vertex.glsl";
            fragment_path = ":/shaders/texture_fragment.glsl";
        } else if (opt_.shading_type == kFlat) {
            vertex_path = ":/shaders/texture_vertex.glsl";
            fragment_path = ":/shaders/texture_flat_fragment.glsl";
        }
    } else if (opt_.model_type == kTextured && !data_.is_normals) {
        vertex_path = ":/shaders/texture_no_normals_vertex.glsl";
        fragment_path = ":/shaders/texture_no_normals_fragment.glsl";
    }
    program_->addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path);
    program_->addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_path);
}

void OpenGL::ProgramCreate() {
    program_ = new QOpenGLShaderProgram(this);

    AddShaders();

    program_->link();
    program_->bind();

    uniforms_[kMvU] = program_->uniformLocation("u_mv");
    uniforms_[kMvpU] = program_->uniformLocation("u_mvp");
    uniforms_[kColorU] = program_->uniformLocation("u_color");
    uniforms_[kAmbientU] = program_->uniformLocation("u_ambient");
    uniforms_[kDiffuseU] = program_->uniformLocation("u_diffuse");
    uniforms_[kShinessU] = program_->uniformLocation("u_shiness");
    uniforms_[kOpacityU] = program_->uniformLocation("u_opacity");
    uniforms_[kSpecularU] = program_->uniformLocation("u_specular");
    uniforms_[kEmissionU] = program_->uniformLocation("u_emission");
    uniforms_[kMatNormalU] = program_->uniformLocation("u_normal_mat");
    uniforms_[kVertexSizeU] = program_->uniformLocation("u_vertex_size");

    program_->setUniformValue("u_texture_a", 0);
    program_->setUniformValue("u_texture_d", 1);
    program_->setUniformValue("u_texture_s", 2);

    vao_.create();
    vao_.bind();

    vbo_.create();
    vbo_.bind();
    vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

    ebo_.create();
    ebo_.bind();
    ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

    program_->enableAttributeArray("a_position");
    if (opt_.model_type == kFrame || opt_.model_type == kDashed) {
        program_->setAttributeBuffer("a_position", GL_FLOAT, 0, 3);
        vbo_.allocate(data_.vertexes_v.data(), data_.vertexes_v.size() * sizeof(float));
        ebo_.allocate(data_.edges.data(), data_.edges.size() * sizeof(unsigned int));
    } else if (opt_.model_type != kFrame && opt_.model_type != kDashed && (data_.is_normals || data_.is_texture)) {
        size_t stride = (3 + 3 * data_.is_normals + 2 * data_.is_texture) * sizeof(float);
        vbo_.allocate(data_.vertexes.data(), data_.vertexes.size() * sizeof(float));
        ebo_.allocate(data_.facets.data(), data_.facets.size() * sizeof(unsigned int));
        program_->setAttributeBuffer("a_position", GL_FLOAT, 0, 3, stride);
        if (data_.is_texture) {
            program_->enableAttributeArray("a_tex_coords");
            program_->setAttributeBuffer("a_tex_coords", GL_FLOAT, 3 * sizeof(float), 2, stride);
        }
        if (data_.is_normals) {
            program_->enableAttributeArray("a_normal");
            program_->setAttributeBuffer("a_normal", GL_FLOAT, 5 * sizeof(float), 3, stride);
        }
    }

    vao_.release();
    vbo_.release();
    ebo_.release();
}

void OpenGL::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ProgramCreate();
}

void OpenGL::resizeGL(int width, int height) {
    ortho_mat_.setToIdentity();
    perspective_mat_.setToIdentity();
    GLfloat coord_x = std::abs(data_.min_coord[0] - data_.max_coord[0]);
    GLfloat coord_y = std::abs(data_.min_coord[1] - data_.max_coord[1]);
    GLfloat coord_z = std::abs(data_.min_coord[2] - data_.max_coord[2]);
    GLfloat mid_coord_x = (data_.min_coord[0] + data_.max_coord[0]) / 2.0f;
    GLfloat mid_coord_y = (data_.min_coord[1] + data_.max_coord[1]) / 2.0f;
    GLfloat mid_coord_z = (data_.min_coord[2] + data_.max_coord[2]) / 2.0f;
    GLfloat max_coord = std::max(std::max(coord_x, coord_y), coord_z);
    GLfloat ratio = GLfloat(width) / GLfloat(height);
    QVector3D center(mid_coord_x, mid_coord_y, mid_coord_z);
    if (opt_.projection_type == kCentral) {
        ortho_mat_.lookAt(QVector3D(center.x(), center.y(), center.z() + max_coord), center, QVector3D(0.0f, 1.0f, 0.0f));
        perspective_mat_.perspective(100.0f, ratio, 0.01f * max_coord, 100.0f * max_coord);
    } else {
        perspective_mat_.ortho(-max_coord * ratio, max_coord * ratio, -max_coord, max_coord, -100.0f * max_coord, 100.0f * max_coord);
    }
    program_->setUniformValue("u_light_pos", QVector3D(center.x(), center.y(), center.z() + max_coord * 3));
    program_->setUniformValue("u_resolution", width, height);
    program_->release();
}

void OpenGL::paintGL() {
    glClearColor(opt_.main_color.redF(), opt_.main_color.greenF(),
                 opt_.main_color.blueF(), opt_.main_color.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(opt_.line_size);

    program_->bind();
    vao_.bind();

    QMatrix4x4 pos = ortho_mat_ * move_mat_ * rotate_mat_ * scale_mat_;
    glUniformMatrix4fv(uniforms_[kMvpU], 1, GL_FALSE, (perspective_mat_ * pos).constData());
    glUniformMatrix4fv(uniforms_[kMvU], 1, GL_FALSE, pos.constData());
    glUniformMatrix4fv(uniforms_[kMatNormalU], 1, GL_FALSE, pos.inverted().transposed().constData());

    program_->setUniformValue(uniforms_[kColorU], opt_.line_color);
    program_->setUniformValue(uniforms_[kVertexSizeU], opt_.vertex_size);
    if (opt_.model_type == kFrame || opt_.model_type == kDashed) {
        glDrawElements(GL_LINES, data_.facets_v.size(), GL_UNSIGNED_INT, 0);
        if (opt_.vertex_type == kSquare) {
            program_->setUniformValue(uniforms_[kColorU], opt_.vertex_color);
            glDrawElements(GL_POINTS, data_.facets_v.size(), GL_UNSIGNED_INT, nullptr);
        } else if (opt_.vertex_type == kCircle) {
            program_->setUniformValue(uniforms_[kColorU], opt_.vertex_color);
            glEnable(GL_POINT_SMOOTH);
            glDrawElements(GL_POINTS, data_.facets_v.size(), GL_UNSIGNED_INT, nullptr);
            glDisable(GL_POINT_SMOOTH);
        }
    } else if ((opt_.model_type == kSolid || opt_.model_type == kTextured) && (data_.is_normals || data_.is_texture)) {
        size_t prev_offset = 0;
        for (auto &usemtl : data_.usemtl) {
            program_->setUniformValue(uniforms_[kAmbientU], &data_.mtl[usemtl.index].Ka);
            program_->setUniformValue(uniforms_[kDiffuseU], &data_.mtl[usemtl.index].Kd);
            program_->setUniformValue(uniforms_[kSpecularU], &data_.mtl[usemtl.index].Ks);
            program_->setUniformValue(uniforms_[kEmissionU], &data_.mtl[usemtl.index].Ke);
            program_->setUniformValue(uniforms_[kShinessU], data_.mtl[usemtl.index].Ns);
            program_->setUniformValue(uniforms_[kOpacityU], data_.mtl[usemtl.index].d);

            if (opt_.model_type == kTextured) {
                maps_[usemtl.index].ambient.bind(0);
                maps_[usemtl.index].diffuse.bind(1);
                maps_[usemtl.index].specular.bind(2);
            }

            glDrawElements(GL_TRIANGLES, usemtl.offset_fv - prev_offset, GL_UNSIGNED_INT, (void*)(prev_offset * sizeof(GLuint)));

            prev_offset = usemtl.offset_fv;
            if (opt_.model_type == kTextured) {
                maps_[usemtl.index].ambient.release(0);
                maps_[usemtl.index].diffuse.release(1);
                maps_[usemtl.index].specular.release(2);
            }
        }
    }

    vao_.release();
    program_->release();
}

void OpenGL::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            Move(-1.0f, kX);
            break;
        case Qt::Key_Right:
            Move(1.0f, kX);
            break;
        case Qt::Key_Up:
            Move(1.0f, kY);
            break;
        case Qt::Key_Down:
            Move(-1.0f, kY);
            break;
        default:
            break;
    }
}

void OpenGL::wheelEvent(QWheelEvent *event) {
    int delta = event->angleDelta().y();
    if (delta > 0)
        Scale(1.1f, kScaleMul);
    else
        Scale(1.1f, kScaleDiv);
}

void OpenGL::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        last_mouse_pos_ = event->pos();
}

void OpenGL::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int delta_x = event->pos().x() - last_mouse_pos_.x();
        int delta_y = event->pos().y() - last_mouse_pos_.y();
        rotate_mat_.setToIdentity();
        angles_[kX] += delta_y / 2;
        angles_[kX] = fmod(angles_[kX], 360.0);
        angles_[kY] += delta_x / 2;
        angles_[kY] = fmod(angles_[kY], 360.0);
        rotate_mat_.rotate(angles_.x(), 1.0f, 0.0f, 0.0f);
        rotate_mat_.rotate(angles_.y(), 0.0f, 1.0f, 0.0f);
        rotate_mat_.rotate(angles_.z(), 0.0f, 0.0f, 1.0f);
        last_mouse_pos_ = event->pos();
        update();
    }
}
}  // namespace s21

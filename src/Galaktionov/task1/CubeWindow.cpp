#include "CubeWindow.h"

CubeWindow::CubeWindow(QWindow *parent)
    : fgl::GLWindow(parent), m_shader_texture(nullptr), m_index_buffer(QOpenGLBuffer::IndexBuffer)
{
}

void CubeWindow::init()//called once
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//rgb and 0-transparent 1-opaque

    glEnable(GL_DEPTH_TEST);//depth buffer
    glEnable(GL_CULL_FACE);//clipping back faces

    //shaders
    m_shader_program = std::make_unique<QOpenGLShaderProgram>(this);
    m_shader_program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader.vsh");
    m_shader_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader.fsh");
    m_shader_program->link();

    //TEXTURE
    m_shader_texture = std::shared_ptr<QOpenGLTexture>(new QOpenGLTexture(QImage(":/cube.jpg").mirrored()));
    //Set nearest filtering mode for texture minification
    m_shader_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    //Set bilinear filtering mode for texture magnification
    m_shader_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    //Wrap texture coordinates by repeating
    m_shader_texture->setWrapMode(QOpenGLTexture::Repeat);

    Init_Cube(0.0f, 0.0f, 0.0f, 1.0f);

    matrixUniform_ = m_shader_program->uniformLocation("qt_ModelViewProjectionMatrix");
    vertex_location = m_shader_program->attributeLocation("qt_Vertex");
    texture_location = m_shader_program->attributeLocation("qt_MultiTexCoord0");
}

void CubeWindow::render()//paint
{
    const auto retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear buffers

    QMatrix4x4 model_view_matrix;
    model_view_matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
    model_view_matrix.translate(0.0, 0.0, -3.0);
    model_view_matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

    m_shader_texture->bind(0);

    m_shader_program->bind();
    m_shader_program->setUniformValue("qt_ModelViewProjectionMatrix", m_projection_matrix * model_view_matrix);
    m_shader_program->setUniformValue("qt_Texture0", 0);

    int offset = 0;

    m_shader_program->enableAttributeArray(vertex_location);
    m_shader_program->setAttributeBuffer(vertex_location, GL_FLOAT, offset, 3, sizeof(Vertex_Data));

    offset += sizeof(QVector3D);

    m_shader_program->enableAttributeArray(texture_location);
    m_shader_program->setAttributeBuffer(texture_location, GL_FLOAT, offset, 2, sizeof(Vertex_Data));

    m_vertex_buffer.bind();
    m_index_buffer.bind();

    glDrawElements(GL_TRIANGLES, m_index_buffer.size(), GL_UNSIGNED_INT, nullptr);//draw triangles

    ++frame_;
}

void CubeWindow::Init_Cube(float x, float y, float z, float width)
{
    float wd2 = width / 2.0f;//wd2 = width divided by 2
    QVector<Vertex_Data> vertexes;

    //z
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y + wd2, z + wd2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y - wd2, z + wd2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y + wd2, z + wd2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y - wd2, z + wd2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)});
    //x
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y - wd2, z + wd2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y - wd2, z - wd2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y + wd2, z + wd2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y + wd2, z - wd2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)});
    //y
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y + wd2, z + wd2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y + wd2, z - wd2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y + wd2, z + wd2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y + wd2, z - wd2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)});
    //-z
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y + wd2, z - wd2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y - wd2, z - wd2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y + wd2, z - wd2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y - wd2, z - wd2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)});
    //-x
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y + wd2, z + wd2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y + wd2, z - wd2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y - wd2, z + wd2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y - wd2, z - wd2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)});
    //-y
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y - wd2, z + wd2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x - wd2, y - wd2, z - wd2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y - wd2, z + wd2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)});
    vertexes.append(Vertex_Data{QVector3D(x + wd2, y - wd2, z - wd2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)});

    QVector<GLuint> indexes;
    for (int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_vertex_buffer.create();
    m_vertex_buffer.bind();
    m_vertex_buffer.allocate(vertexes.constData(), vertexes.size() * sizeof(Vertex_Data));

    m_index_buffer.create();
    m_index_buffer.bind();
    m_index_buffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  mousePressPosition = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(event->localPos()) - mousePressPosition;

  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}


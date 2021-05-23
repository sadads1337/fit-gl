#include "CubeWindow.h"

std::array<QVector3D, 17> cubes_arr{
            QVector3D(-0.5f, 0.0f,-1.0f),QVector3D( 0.5f, 0.0f,-1.0f),

            QVector3D(-2.0f, 1.0f,-2.5f),QVector3D(-2.0f, 0.0f,-2.5f),QVector3D(-2.0f,-1.0f,-2.5f),
            QVector3D(-1.0f, 1.0f,-2.5f),QVector3D(-1.0f, 0.0f,-2.5f),QVector3D(-1.0f,-1.0f,-2.5f),
            QVector3D( 0.0f, 1.0f,-2.5f),QVector3D( 0.0f, 0.0f,-2.5f),QVector3D( 0.0f,-1.0f,-2.5f),
            QVector3D( 1.0f, 1.0f,-2.5f),QVector3D( 1.0f, 0.0f,-2.5f),QVector3D( 1.0f,-1.0f,-2.5f),
            QVector3D( 2.0f, 1.0f,-2.5f),QVector3D( 2.0f, 0.0f,-2.5f),QVector3D( 2.0f,-1.0f,-2.5f)
};

std::array<Vertex_Data, 24> vertexes{{
        //z
        Vertex_Data{{-0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}},
        Vertex_Data{{-0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}},
        Vertex_Data{{ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}},
        Vertex_Data{{ 0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}},
        //x
        Vertex_Data{{ 0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f}},
        Vertex_Data{{ 0.5f,-0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f}},
        Vertex_Data{{ 0.5f, 0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f}},
        Vertex_Data{{ 0.5f, 0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f}},
        //y
        Vertex_Data{{ 0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f}},
        Vertex_Data{{ 0.5f, 0.5f,-0.5f}, { 0.0f, 1.0f, 0.0f}},
        Vertex_Data{{-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f}},
        Vertex_Data{{-0.5f, 0.5f,-0.5f}, { 0.0f, 1.0f, 0.0f}},
        //-z
        Vertex_Data{{ 0.5f, 0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}},
        Vertex_Data{{ 0.5f,-0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}},
        Vertex_Data{{-0.5f, 0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}},
        Vertex_Data{{-0.5f,-0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}},
        //-x
        Vertex_Data{{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}},
        Vertex_Data{{-0.5f, 0.5f,-0.5f}, {-1.0f, 0.0f, 0.0f}},
        Vertex_Data{{-0.5f,-0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}},
        Vertex_Data{{-0.5f,-0.5f,-0.5f}, {-1.0f, 0.0f, 0.0f}},
        //-y
        Vertex_Data{{-0.5f,-0.5f, 0.5f}, { 0.0f,-1.0f, 0.0f}},
        Vertex_Data{{-0.5f,-0.5f,-0.5f}, { 0.0f,-1.0f, 0.0f}},
        Vertex_Data{{ 0.5f,-0.5f, 0.5f}, { 0.0f,-1.0f, 0.0f}},
        Vertex_Data{{ 0.5f,-0.5f,-0.5f}, { 0.0f,-1.0f, 0.0f}}
                                      }};

std::array<GLuint, 36> indexes{{
        //z
         0,  1,  2,  2,  1,  3,
        //x
         4,  5,  6,  6,  5,  7,
        //y
         8,  9, 10, 10,  9, 11,
        //-z
        12, 13, 14, 14, 13, 15,
        //-x
        16, 17, 18, 18, 17, 19,
        //-y
        20, 21, 22, 22, 21, 23
                                }};

void CubeWindow::init()//called once
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//rgb and 0-transparent 1-opaque

    glEnable(GL_DEPTH_TEST);//depth buffer
    glEnable(GL_CULL_FACE);//clipping back faces

    //shader
    m_shader_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader.vs");
    m_shader_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader.fs");
    m_shader_program.link();

    //vertex buffer
    m_vertex_buffer.create();
    m_vertex_buffer.bind();
    m_vertex_buffer.allocate(vertexes.data(), vertexes.size() * sizeof(Vertex_Data));

    //index buffer
    m_index_buffer.create();
    m_index_buffer.bind();
    m_index_buffer.allocate(indexes.data(), indexes.size() * sizeof(GLuint));

    //attributes and uniforms
    matrixUniform_ = m_shader_program.uniformLocation("qt_ModelViewProjectionMatrix");
    vertex_location = m_shader_program.attributeLocation("qt_Vertex");
    normal = m_shader_program.attributeLocation("qt_Normal");

    //set attribute buffers
    int offset = 0;
    m_shader_program.setAttributeBuffer(vertex_location, GL_FLOAT, offset, 3, sizeof(Vertex_Data));
    offset += sizeof(QVector3D);
    m_shader_program.setAttributeBuffer(normal, GL_FLOAT, offset, 3, sizeof(Vertex_Data));
}

void CubeWindow::render()//paint
{
    //viewport
    const auto retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear buffers

    m_shader_program.bind();//bind shader

    for (int i = 0; i < int(cubes_arr.size()); i++) {
        //model view projection matrix
        QMatrix4x4 model_view_matrix;
        model_view_matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
        model_view_matrix.translate(cubes_arr[i]);
        if (i == 9) model_view_matrix.rotate(312.5, QVector3D(5.9f,-3.2f,1.0f).normalized());//center
        else model_view_matrix.rotate(10.0 * (i + 1) * frame_ / screen()->refreshRate(), (rotationAxis + QVector3D(1 + i, 2 - i, 3 + i).normalized()).normalized());//other
        model_view_matrix.scale(0.3f, 0.3f, 0.3f);

        //set uniforms
        m_shader_program.setUniformValue(matrixUniform_, model_view_matrix);
        m_shader_program.setUniformValue("qt_NormalMatrix", model_view_matrix.normalMatrix());
        m_shader_program.setUniformValue("qt_color_set", changeColor);
        m_shader_program.setUniformValue("qt_ModeChange", 1);//GOURAUD -> 0 or PHONG -> 1

        //enable attribute array
        m_shader_program.enableAttributeArray(normal);
        m_shader_program.enableAttributeArray(vertex_location);

        glDrawElements(GL_TRIANGLES, m_index_buffer.size(), GL_UNSIGNED_INT, 0);//draw triangles

        //disable attribute array
        m_shader_program.disableAttributeArray(vertex_location);
        m_shader_program.disableAttributeArray(normal);
    }
    m_shader_program.release();
    ++frame_;//counter
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    QColor color = QColorDialog::getColor();
    changeColor = QVector4D(color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  mousePressPosition_ = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(event->localPos()) - mousePressPosition_;

  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0f).normalized();
}

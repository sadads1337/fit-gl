#include "MainWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <array>

namespace Kononov {

constexpr std::array<GLfloat, 192u> modelVertices = {
    -1.0f, -1.0f, 1.0f, 0, 0, 1, 0.0f, 0.0f,  // v0
    1.0f, -1.0f, 1.0f, 0, 0, 1, 0.333f, 0.0f, // v1
    -1.0f, 1.0f, 1.0f, 0, 0, 1, 0.0f, 0.5f,   // v2
    1.0f, 1.0f, 1.0f, 0, 0, 1, 0.333f, 0.5f,  // v3

    // Vertex data for face 1
    1.0f, -1.0f, 1.0f, 1, 0, 0, 0.0f, 0.5f,    // v4
    1.0f, -1.0f, -1.0f, 1, 0, 0, 0.333f, 0.5f, // v5
    1.0f, 1.0f, 1.0f, 1, 0, 0, 0.0f, 1.0f,     // v6
    1.0f, 1.0f, -1.0f, 1, 0, 0, 0.333f, 1.0f,  // v7

    // Vertex data for face 2
    1.0f, -1.0f, -1.0f, 0, 0, -1, 0.666f, 0.5f, // v8
    -1.0f, -1.0f, -1.0f, 0, 0, -1, 1.0f, 0.5f,  // v9
    1.0f, 1.0f, -1.0f, 0, 0, -1, 0.666f, 1.0f,  // v10
    -1.0f, 1.0f, -1.0f, 0, 0, -1, 1.0f, 1.0f,   // v11

    // Vertex data for face 3
    -1.0f, -1.0f, -1.0f, -1, 0, 0, 0.666f, 0.0f, // v12
    -1.0f, -1.0f, 1.0f, -1, 0, 0, 1.0f, 0.0f,    // v13
    -1.0f, 1.0f, -1.0f, -1, 0, 0, 0.666f, 0.5f,  // v14
    -1.0f, 1.0f, 1.0f, -1, 0, 0, 1.0f, 0.5f,     // v15

    // Vertex data for face 4
    -1.0f, -1.0f, -1.0f, 0, -1, 0, 0.333f, 0.0f, // v16
    1.0f, -1.0f, -1.0f, 0, -1, 0, 0.666f, 0.0f,  // v17
    -1.0f, -1.0f, 1.0f, 0, -1, 0, 0.333f, 0.5f,  // v18
    1.0f, -1.0f, 1.0f, 0, -1, 0, 0.666f, 0.5f,   // v19

    // Vertex data for face 5
    -1.0f, 1.0f, 1.0f, 0, 1, 0, 0.333f, 0.5f,  // v20
    1.0f, 1.0f, 1.0f, 0, 1, 0, 0.666f, 0.5f,   // v21
    -1.0f, 1.0f, -1.0f, 0, 1, 0, 0.333f, 1.0f, // v22
    1.0f, 1.0f, -1.0f, 0, 1, 0, 0.666f, 1.0f   // v23
};

// Indices for drawing cube faces using triangle strips.
// Triangle strips can be connected by duplicating indices
// between the strips. If connecting strips have opposite
// vertex order then last index of the first strip and first
// index of the second strip needs to be duplicated. If
// connecting strips have same vertex order then only last
// index of the first strip needs to be duplicated.
constexpr std::array<GLushort, 34u> modelIndices = {
    0,  1,  2,  3,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    4,  4,  5,  6,  7,  7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    8,  8,  9,  10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
};

void MainWindow::onMessageLogged(QOpenGLDebugMessage message) {
  qDebug() << message;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  m_look_dir->mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  m_look_dir->mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  m_look_dir->mouseReleaseEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  m_motion->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  m_motion->keyReleaseEvent(event);
}

void MainWindow::init() {
  /*
   * Logger initialization
   */
  m_logger = std::make_unique<QOpenGLDebugLogger>(this);

  connect(m_logger.get(), &QOpenGLDebugLogger::messageLogged, this,
          &MainWindow::onMessageLogged);

  if (m_logger->initialize()) {
    m_logger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
    m_logger->enableMessages();
  }

  /*
   * Create and initialize shader program
   */
  m_program = std::make_unique<FirstShader>();

  /*
   * Create VBO/IBO (they can be created independently)
   */

  m_vbo = std::make_unique<QOpenGLBuffer>(QOpenGLBuffer::Type::VertexBuffer);
  m_vbo->create();
  m_vbo->bind();
  // Fill it
  m_vbo->allocate(modelVertices.data(), modelVertices.size() * sizeof(GLfloat));
  // Do not release VBO. We still need it.

  m_ibo = std::make_unique<QOpenGLBuffer>(QOpenGLBuffer::Type::IndexBuffer);
  m_ibo->create();
  m_ibo->bind();
  // Fill it
  m_ibo->allocate(modelIndices.data(), modelIndices.size() * sizeof(GLushort));
  m_ibo->release(); // We do not need IBO for further initialization

  /*
   * Create and configure VBO
   */
  m_vao = std::make_unique<QOpenGLVertexArrayObject>();
  m_vao->create();
  m_vao->bind();

  // glVertexAttribPointer (specify location of values in vertex structure)
  // NOTE: VBO is still bound
  m_program->setVertexPositionBuffer(sizeof(GLfloat) * 0, sizeof(GLfloat) * 8);
  m_program->setVertexNormalBuffer(sizeof(GLfloat) * 3, sizeof(GLfloat) * 8);
  m_program->setVertexUVBuffer(sizeof(GLfloat) * 6, sizeof(GLfloat) * 8);

  m_vbo->release();
  m_vao->release();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  m_look_dir = std::make_shared<DirectionInputController>();
  m_motion = std::make_shared<MotionInputController>(m_look_dir);

  m_motion->setPosition(QVector3D(0, 1.3, 4));

  initTextures();
}

void MainWindow::initTextures() {
  m_diffuse_map = std::make_unique<QOpenGLTexture>(
      QImage(":/textures/dice-diffuse.png").mirrored());
  m_diffuse_map->setMinificationFilter(QOpenGLTexture::Nearest);
  m_diffuse_map->setMagnificationFilter(QOpenGLTexture::Linear);
  m_diffuse_map->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWindow::render() {
  m_motion->update();

  const auto pixel_ratio = devicePixelRatio();
  const auto ratio = (float)width() / (float)height();

  glViewport(0, 0, width() * pixel_ratio, height() * pixel_ratio);

  glClearColor(0, 0.5, 1, 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 view_matrix;
  view_matrix.perspective(60.0f, ratio, 0.1f, 100.0f);
  view_matrix.rotate(m_look_dir->getRotation());
  view_matrix.translate(-m_motion->getPosition());

  QMatrix4x4 model_matrix;
  model_matrix.rotate(30.0 * m_frame / screen()->refreshRate(), 0, 1, 0);

  // To render we need to use concrete m_program, VAO and IBO (VBO is referenced
  // by VAO)
  m_program->bind();
  m_vao->bind();
  m_ibo->bind();
  m_diffuse_map->bind();

  m_program->setMatrices(view_matrix, model_matrix);
  m_program->setViewPosition(m_motion->getPosition());
  m_program->setLightSource(QVector3D(3, 2, 0), QVector3D(1, 0.7, 0.7));
  m_program->setDiffuseMap(0);
  m_program->setAmbient(0.3f);
  m_program->setSpecular(0.5f, 32);

  // glEnableVertexAttribArray (allow current VAO to affect attribute)
  m_program->enableAttributeArrays();

  glDrawElements(GL_TRIANGLE_STRIP, modelIndices.size(), GL_UNSIGNED_SHORT,
                 (void *)0); // NOLINT(modernize-use-nullptr)

  // glDisableVertexAttribArray (because it is not bound to m_program ??? and
  // can affect further rendering)
  m_program->disableAttributeArrays();

  m_ibo->release();
  m_vao->release();
  m_program->release();

  m_frame++;
}

} // namespace Kononov

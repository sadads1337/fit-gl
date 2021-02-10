#include "MainWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <array>

namespace Kononov {

constexpr std::array<GLfloat, 192U> modelVertices = {
    -1.0F, -1.0F, 1.0F, 0, 0, 1, 0.0F, 0.0F,  // v0
    1.0F, -1.0F, 1.0F, 0, 0, 1, 0.333F, 0.0F, // v1
    -1.0F, 1.0F, 1.0F, 0, 0, 1, 0.0F, 0.5F,   // v2
    1.0F, 1.0F, 1.0F, 0, 0, 1, 0.333F, 0.5F,  // v3

    // Vertex data for face 1
    1.0F, -1.0F, 1.0F, 1, 0, 0, 0.0F, 0.5F,    // v4
    1.0F, -1.0F, -1.0F, 1, 0, 0, 0.333F, 0.5F, // v5
    1.0F, 1.0F, 1.0F, 1, 0, 0, 0.0F, 1.0F,     // v6
    1.0F, 1.0F, -1.0F, 1, 0, 0, 0.333F, 1.0F,  // v7

    // Vertex data for face 2
    1.0F, -1.0F, -1.0F, 0, 0, -1, 0.666F, 0.5F, // v8
    -1.0F, -1.0F, -1.0F, 0, 0, -1, 1.0F, 0.5F,  // v9
    1.0F, 1.0F, -1.0F, 0, 0, -1, 0.666F, 1.0F,  // v10
    -1.0F, 1.0F, -1.0F, 0, 0, -1, 1.0F, 1.0F,   // v11

    // Vertex data for face 3
    -1.0F, -1.0F, -1.0F, -1, 0, 0, 0.666F, 0.0F, // v12
    -1.0F, -1.0F, 1.0F, -1, 0, 0, 1.0F, 0.0F,    // v13
    -1.0F, 1.0F, -1.0F, -1, 0, 0, 0.666F, 0.5F,  // v14
    -1.0F, 1.0F, 1.0F, -1, 0, 0, 1.0F, 0.5F,     // v15

    // Vertex data for face 4
    -1.0F, -1.0F, -1.0F, 0, -1, 0, 0.333F, 0.0F, // v16
    1.0F, -1.0F, -1.0F, 0, -1, 0, 0.666F, 0.0F,  // v17
    -1.0F, -1.0F, 1.0F, 0, -1, 0, 0.333F, 0.5F,  // v18
    1.0F, -1.0F, 1.0F, 0, -1, 0, 0.666F, 0.5F,   // v19

    // Vertex data for face 5
    -1.0F, 1.0F, 1.0F, 0, 1, 0, 0.333F, 0.5F,  // v20
    1.0F, 1.0F, 1.0F, 0, 1, 0, 0.666F, 0.5F,   // v21
    -1.0F, 1.0F, -1.0F, 0, 1, 0, 0.333F, 1.0F, // v22
    1.0F, 1.0F, -1.0F, 0, 1, 0, 0.666F, 1.0F   // v23
};

// Indices for drawing cube faces using triangle strips.
// Triangle strips can be connected by duplicating indices
// between the strips. If connecting strips have opposite
// vertex order then last index of the first strip and first
// index of the second strip needs to be duplicated. If
// connecting strips have same vertex order then only last
// index of the first strip needs to be duplicated.
constexpr std::array<GLushort, 34U> modelIndices = {
    0,  1,  2,  3,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    4,  4,  5,  6,  7,  7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    8,  8,  9,  10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
};

static constexpr QVector3D INITIAL_CAMERA_POSITION(0, 1.3, 4);
static constexpr QVector3D LIGHT_POSITION(3, 2, 0);
static constexpr QVector3D LIGHT_COLOR(1, 0.7, 0.7);
static constexpr QVector4D CLEAR_COLOR(0, 0.5, 1, 1);

static const float PERSPECTIVE_FOV = 60.0F;
static const float NEAR_PLANE = 0.1F;
static const float FAR_PLANE = 100.0F;

static const float AMBIENT_STRENGTH = 0.3F;
static const float SPECULAR_STRENGTH = 0.5F;
static const int SPECULAR_POW = 32;

static const float MOUSE_SENSITIVITY = 0.2F;
static const float ROTATION_SPEED = 30.0F;
static const float MOTION_SPEED = 0.1F;

void MainWindow::onMessageLogged(const QOpenGLDebugMessage &message) {
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
  const size_t stride = sizeof(GLfloat) * 8;
  const size_t pos_offset = sizeof(GLfloat) * 0;
  const size_t normal_offset = sizeof(GLfloat) * 3;
  const size_t uv_offset = sizeof(GLfloat) * 6;
  m_program->setVertexPositionBuffer(pos_offset, stride);
  m_program->setVertexNormalBuffer(normal_offset, stride);
  m_program->setVertexUVBuffer(uv_offset, stride);

  m_vbo->release();
  m_vao->release();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  m_look_dir = std::make_shared<DirectionInputController>();
  m_look_dir->setSensitivity(MOUSE_SENSITIVITY);
  m_motion = std::make_shared<MotionInputController>(m_look_dir);
  m_motion->setMotionSpeed(MOTION_SPEED);
  m_motion->setPosition(INITIAL_CAMERA_POSITION);

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

  glViewport(0, 0, (GLsizei)(width() * pixel_ratio),
             (GLsizei)(height() * pixel_ratio));

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(),
               CLEAR_COLOR.w());

  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 view_matrix;
  view_matrix.perspective(PERSPECTIVE_FOV, ratio, NEAR_PLANE, FAR_PLANE);
  view_matrix.rotate(m_look_dir->getRotation());
  view_matrix.translate(-m_motion->getPosition());

  const float angle =
      ROTATION_SPEED * (float)m_frame / (float)screen()->refreshRate();
  QMatrix4x4 model_matrix;
  model_matrix.rotate(angle, 0, 1, 0);

  // To render we need to use concrete program, VAO and IBO (VBO is referenced
  // by VAO)
  m_program->bind();
  m_vao->bind();
  m_ibo->bind();
  m_diffuse_map->bind();

  m_program->setMatrices(view_matrix, model_matrix);
  m_program->setViewPosition(m_motion->getPosition());
  m_program->setLightSource(LIGHT_POSITION, LIGHT_COLOR);
  m_program->setDiffuseMap(0);
  m_program->setAmbient(AMBIENT_STRENGTH);
  m_program->setSpecular(SPECULAR_STRENGTH, SPECULAR_POW);

  // glEnableVertexAttribArray (allow current VAO to affect attribute)
  m_program->enableAttributeArrays();

  glDrawElements(GL_TRIANGLE_STRIP, modelIndices.size(), GL_UNSIGNED_SHORT,
                 nullptr);

  // glDisableVertexAttribArray (because it is not bound to m_program ??? and
  // can affect further rendering)
  m_program->disableAttributeArrays();

  m_ibo->release();
  m_vao->release();
  m_program->release();

  m_frame++;
}

} // namespace Kononov

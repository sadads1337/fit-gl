#include "MainWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <array>

#include "ShaderProgram.hpp"

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
constexpr std::array<GLuint, 34U> modelIndices = {
    0,  1,  2,  3,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    4,  4,  5,  6,  7,  7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    8,  8,  9,  10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
};

static constexpr QVector3D INITIAL_CAMERA_POSITION(0, 1.3, 4);
static constexpr QVector3D LIGHT_POSITION(3, 2, 3);
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

  m_shader = std::make_shared<FirstShader>();

  m_skull = std::make_unique<FirstRenderable>(GL_TRIANGLES, m_shader,
                                              ":/textures/skull-diffuse.jpg",
                                              ":/models/skull.vbo-ibo");
  m_skull->getShaderParameters().setLightSource(LIGHT_POSITION, LIGHT_COLOR);
  m_skull->getShaderParameters().setDiffuseMap(0);
  m_skull->getShaderParameters().setAmbient(AMBIENT_STRENGTH);
  m_skull->getShaderParameters().setSpecular(SPECULAR_STRENGTH, SPECULAR_POW);

  m_cube = std::make_unique<FirstRenderable>(
      GL_TRIANGLE_STRIP, m_shader, ":/textures/dice-diffuse.png",
      (char *)modelVertices.data(), modelVertices.size() * sizeof(GLfloat),
      (char *)modelIndices.data(), modelIndices.size() * sizeof(GLfloat));
  m_cube->setShaderParameters(m_skull->getShaderParameters());

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  m_look_dir = std::make_shared<DirectionInputController>();
  m_look_dir->setSensitivity(MOUSE_SENSITIVITY);
  m_motion = std::make_shared<MotionInputController>(m_look_dir);
  m_motion->setMotionSpeed(MOTION_SPEED);
  m_motion->setPosition(INITIAL_CAMERA_POSITION);
}

void MainWindow::render() {
  m_motion->update();

  const auto pixel_ratio = devicePixelRatio();
  const auto ratio = (float)width() / (float)height();

  glViewport(0, 0, (GLsizei)(width() * pixel_ratio / 2),
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
  const float model_scale = 0.1F;
  QMatrix4x4 model_matrix;
  model_matrix.rotate(angle, 0, 1, 0);
  model_matrix.scale(model_scale);

  m_skull->getShaderParameters().setViewPos(m_motion->getPosition());
  m_skull->render(view_matrix, model_matrix);

  model_matrix.setToIdentity();
  model_matrix.translate(-3, 0, 0);
  model_matrix.scale(model_scale);

  // View position is same
  m_skull->render(view_matrix, model_matrix);

  model_matrix.setToIdentity();
  model_matrix.translate(4, 0, 0);
  model_matrix.rotate(-angle, 0, 1, 0);

  m_cube->getShaderParameters().setViewPos(m_motion->getPosition());
  m_cube->render(view_matrix, model_matrix);

  m_frame++;
}

} // namespace Kononov

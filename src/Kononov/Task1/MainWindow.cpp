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

static constexpr QVector3D INITIAL_CAMERA_POSITION(0, 1.3, 8);
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
  m_direction_input_controller->mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseReleaseEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  m_motion_input_controller->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  m_motion_input_controller->keyReleaseEvent(event);
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
   * Configure OpenGL
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(),
               CLEAR_COLOR.w());

  /*
   * Load and configure shaders and renderable objects
   */
  auto shader = std::make_shared<FirstShader>();

  auto skull_rend = std::make_shared<FirstRenderable>(
      GL_TRIANGLES, shader, ":/textures/skull-diffuse.jpg",
      ":/models/skull.vbo-ibo");
  skull_rend->getShaderParameters().setLightSource(LIGHT_POSITION, LIGHT_COLOR);
  skull_rend->getShaderParameters().setDiffuseMap(0);
  skull_rend->getShaderParameters().setAmbient(AMBIENT_STRENGTH);
  skull_rend->getShaderParameters().setSpecular(SPECULAR_STRENGTH,
                                                SPECULAR_POW);

  auto cube_rend = std::make_shared<FirstRenderable>(
      GL_TRIANGLE_STRIP, shader, ":/textures/dice-diffuse.png",
      (char *)modelVertices.data(), modelVertices.size() * sizeof(GLfloat),
      (char *)modelIndices.data(), modelIndices.size() * sizeof(GLfloat));
  cube_rend->setShaderParameters(skull_rend->getShaderParameters());

  /*
   * Init scene objects
   */
  const QVector3D skull_scale(0.1F, 0.1F, 0.1F);
  m_skull = std::make_shared<FirstSceneObject>();
  m_skull->setRenderable(skull_rend);
  m_skull->setScale(skull_scale);
  m_skull->setPosition(QVector3D(-3, 0, 0));

  m_skull_rotating = std::make_shared<FirstSceneObject>();
  m_skull_rotating->setRenderable(skull_rend);
  m_skull_rotating->setScale(skull_scale);
  m_skull_rotating->setPosition(QVector3D(0, 0, 0));

  m_cube = std::make_shared<FirstSceneObject>();
  m_cube->setRenderable(cube_rend);
  m_cube->setPosition(QVector3D(4, 0, 0));

  m_camera = std::make_shared<Camera>();
  m_camera->setPosition(INITIAL_CAMERA_POSITION);

  m_direction_input_controller = std::make_shared<DirectionInputController>();
  m_direction_input_controller->setObject(m_camera);
  m_direction_input_controller->setSensitivity(MOUSE_SENSITIVITY);

  m_motion_input_controller = std::make_shared<MotionInputController>();
  m_motion_input_controller->setObject(m_camera);
  m_motion_input_controller->setDirectionSource(m_direction_input_controller);
  m_motion_input_controller->setMotionSpeed(MOTION_SPEED);
}

void MainWindow::render() {
  m_motion_input_controller->update();

  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const auto pixel_ratio = devicePixelRatio();
  const auto ratio = (float)width() / (float)height();
  m_camera->setPerspective(PERSPECTIVE_FOV, ratio, NEAR_PLANE, FAR_PLANE);
  m_camera->beginRender((GLsizei)(width() * pixel_ratio),
                        (GLsizei)(height() * pixel_ratio));

  const float angle =
      ROTATION_SPEED * (float)m_frame / (float)screen()->refreshRate();
  m_skull_rotating->setRotation(QQuaternion::fromAxisAndAngle(0, 1, 0, angle));
  m_skull_rotating->render(*m_camera);
  m_skull->render(*m_camera);
  m_cube->render(*m_camera);

  m_frame++;
}

} // namespace Kononov

#include "SecondWindow.hpp"

#include <cmath>
#include <vector>

#include <QOpenGLFunctions>
#include <QScreen>

#include <Resources.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>

#include "SecondShader.hpp"
#include "TesselatedRenderable.hpp"

namespace {

const std::vector<Kononov::RegularVertex> modelVertices = {
    {{-1.0F, -1.0F, 1.0F}, {0, 0, 1}, {0.0F, 0.0F}},  // v0
    {{1.0F, -1.0F, 1.0F}, {0, 0, 1}, {0.333F, 0.0F}}, // v1
    {{-1.0F, 1.0F, 1.0F}, {0, 0, 1}, {0.0F, 0.5F}},   // v2
    {{1.0F, 1.0F, 1.0F}, {0, 0, 1}, {0.333F, 0.5F}},  // v3

    // Vertex data for face 1
    {{1.0F, -1.0F, 1.0F}, {1, 0, 0}, {0.0F, 0.5F}},    // v4
    {{1.0F, -1.0F, -1.0F}, {1, 0, 0}, {0.333F, 0.5F}}, // v5
    {{1.0F, 1.0F, 1.0F}, {1, 0, 0}, {0.0F, 1.0F}},     // v6
    {{1.0F, 1.0F, -1.0F}, {1, 0, 0}, {0.333F, 1.0F}},  // v7

    // Vertex data for face 2
    {{1.0F, -1.0F, -1.0F}, {0, 0, -1}, {0.666F, 0.5F}}, // v8
    {{-1.0F, -1.0F, -1.0F}, {0, 0, -1}, {1.0F, 0.5F}},  // v9
    {{1.0F, 1.0F, -1.0F}, {0, 0, -1}, {0.666F, 1.0F}},  // v10
    {{-1.0F, 1.0F, -1.0F}, {0, 0, -1}, {1.0F, 1.0F}},   // v11

    // Vertex data for face 3
    {{-1.0F, -1.0F, -1.0F}, {-1, 0, 0}, {0.666F, 0.0F}}, // v12
    {{-1.0F, -1.0F, 1.0F}, {-1, 0, 0}, {1.0F, 0.0F}},    // v13
    {{-1.0F, 1.0F, -1.0F}, {-1, 0, 0}, {0.666F, 0.5F}},  // v14
    {{-1.0F, 1.0F, 1.0F}, {-1, 0, 0}, {1.0F, 0.5F}},     // v15

    // Vertex data for face 4
    {{-1.0F, -1.0F, -1.0F}, {0, -1, 0}, {0.333F, 0.0F}}, // v16
    {{1.0F, -1.0F, -1.0F}, {0, -1, 0}, {0.666F, 0.0F}},  // v17
    {{-1.0F, -1.0F, 1.0F}, {0, -1, 0}, {0.333F, 0.5F}},  // v18
    {{1.0F, -1.0F, 1.0F}, {0, -1, 0}, {0.666F, 0.5F}},   // v19

    // Vertex data for face 5
    {{-1.0F, 1.0F, 1.0F}, {0, 1, 0}, {0.333F, 0.5F}},  // v20
    {{1.0F, 1.0F, 1.0F}, {0, 1, 0}, {0.666F, 0.5F}},   // v21
    {{-1.0F, 1.0F, -1.0F}, {0, 1, 0}, {0.333F, 1.0F}}, // v22
    {{1.0F, 1.0F, -1.0F}, {0, 1, 0}, {0.666F, 1.0F}},  // v23
};

// Indices for drawing cube faces using triangle strips.
// Triangle strips can be connected by duplicating indices
// between the strips. If connecting strips have opposite
// vertex order then last index of the first strip and first
// index of the second strip needs to be duplicated. If
// connecting strips have same vertex order then only last
// index of the first strip needs to be duplicated.
const std::vector<GLuint> modelIndices = {
    0,  1,  2,  2,  1,  3,  4,  5,  6,  6,  5,  7,  8,  9,  10, 10, 9,  11,
    12, 13, 14, 14, 13, 15, 16, 17, 18, 18, 17, 19, 20, 21, 22, 22, 21, 23,
};

} // namespace

namespace Kononov {

constexpr QVector3D INITIAL_CAMERA_POSITION(0.0F, 1.3F, 8.0F);
constexpr QVector3D LIGHT_POSITION(3.0F, 2.0F, 3.0F);
constexpr QVector3D LIGHT_COLOR(1.0F, 0.7F, 0.7F);
constexpr QVector4D CLEAR_COLOR(0.0F, 0.5F, 1.0F, 1.0F);

constexpr float PERSPECTIVE_FOV = 60.0F;
constexpr float NEAR_PLANE = 0.1F;
constexpr float FAR_PLANE = 100.0F;

constexpr float AMBIENT_STRENGTH = 0.3F;
constexpr float SPECULAR_STRENGTH = 0.5F;
constexpr int SPECULAR_POW = 32;

constexpr float MOUSE_SENSITIVITY = 0.2F;
constexpr float ROTATION_SPEED = 0.03F;
constexpr float ROTATION_AMPLITUDE_CUBE = 0.7F;
constexpr float ROTATION_AMPLITUDE_SKULL = 0.1F;
constexpr float MOTION_SPEED = 0.1F;

void SecondWindow::onMessageLogged(const QOpenGLDebugMessage &message) {
  qDebug() << message;
}

void SecondWindow::mousePressEvent(QMouseEvent *event) {
  m_direction_input_controller->mousePressEvent(event);
}

void SecondWindow::mouseMoveEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseMoveEvent(event);
}

void SecondWindow::mouseReleaseEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseReleaseEvent(event);
}

void SecondWindow::keyPressEvent(QKeyEvent *event) {
  m_motion_input_controller->keyPressEvent(event);
}

void SecondWindow::keyReleaseEvent(QKeyEvent *event) {
  m_motion_input_controller->keyReleaseEvent(event);
}

void SecondWindow::init() {
  /*
   * Logger initialization
   */
  m_logger = std::make_unique<QOpenGLDebugLogger>(this);

  connect(m_logger.get(), &QOpenGLDebugLogger::messageLogged, this,
          &SecondWindow::onMessageLogged);

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
  auto program = Resources::loadShaderProgramShared({":/shaders/second.vert",
                                                     ":/shaders/second.geom",
                                                     ":/shaders/second.frag"});

  auto cube_program = Resources::loadShaderProgramShared(
      {":/shaders/second-cube.vert", ":/shaders/second-cube.tesc",
       ":/shaders/second-cube.tese", ":/shaders/second-cube.geom",
       ":/shaders/second.frag"});

  auto skull_texture =
      Resources::loadTextureShared(":/textures/skull-diffuse.jpg");

  auto cube_texture =
      Resources::loadTextureShared(":/textures/dice-diffuse.png");

  auto skull_mesh = Resources::loadMeshShared<RegularVertex, GLuint>(
      ":/models/skull.vbo-ibo", GL_TRIANGLES);

  auto cube_mesh = std::make_shared<GenericMesh<RegularVertex, GLuint>>(
      modelVertices, modelIndices, GL_PATCHES);

  SecondShader factory(program);
  m_skull_shader = factory.createShared();
  m_skull_shader->getParameters().setLightSource(LIGHT_POSITION, LIGHT_COLOR);
  m_skull_shader->getParameters().setDiffuseTexture(skull_texture);
  m_skull_shader->getParameters().setAmbientStrength(AMBIENT_STRENGTH);
  m_skull_shader->getParameters().setSpecular(SPECULAR_STRENGTH, SPECULAR_POW);

  SecondShader cube_factory(cube_program);
  m_cube_shader = cube_factory.createShared();
  m_cube_shader->setParameters(m_skull_shader->getParameters());
  m_cube_shader->getParameters().setDiffuseTexture(cube_texture);

  auto skull_rend = std::make_shared<GenericRenderable>(
      std::dynamic_pointer_cast<TypedShader<RegularVertex::Interface>>(
          m_skull_shader),
      std::dynamic_pointer_cast<TypedMesh<RegularVertex>>(skull_mesh));

  auto cube_rend = std::make_shared<TesselatedRenderable>(
      std::dynamic_pointer_cast<TypedShader<RegularVertex::Interface>>(
          m_cube_shader),
      std::dynamic_pointer_cast<TypedMesh<RegularVertex>>(cube_mesh), 3);

  /*
   * Init scene objects
   */
  const QVector3D skull_scale(0.1F, 0.1F, 0.1F);
  m_skull = std::make_shared<SceneObject>();
  m_skull->setRenderable(skull_rend);
  m_skull->setScale(skull_scale);
  m_skull->setPosition(QVector3D(-2, 0, 0));

  m_cube = std::make_shared<SceneObject>();
  m_cube->setRenderable(cube_rend);
  m_cube->setPosition(QVector3D(2, 0, 0));

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

void SecondWindow::render() {
  m_motion_input_controller->update();

  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const auto pixel_ratio = devicePixelRatio();
  const auto ratio = static_cast<float>(width()) / static_cast<float>(height());
  m_camera->setPerspective(PERSPECTIVE_FOV, ratio, NEAR_PLANE, FAR_PLANE);
  m_camera->beginRender((GLsizei)(width() * pixel_ratio),
                        (GLsizei)(height() * pixel_ratio));

  m_cube_shader->getParameters().setSkewness(
      ROTATION_AMPLITUDE_CUBE *
      std::sin(static_cast<float>(m_frame) * ROTATION_SPEED));
  m_cube->render(*m_camera);

  m_skull_shader->getParameters().setSkewness(
      ROTATION_AMPLITUDE_SKULL *
      std::cos(static_cast<float>(m_frame) * ROTATION_SPEED));
  m_skull->render(*m_camera);

  m_frame++;
}

} // namespace Kononov

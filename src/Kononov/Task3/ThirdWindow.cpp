#include "ThirdWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <CubeMesh.hpp>
#include <Resources.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>

namespace Kononov {

constexpr QVector3D INITIAL_CAMERA_POSITION(0.0F, 1.3F, 8.0F);
constexpr QVector3D LIGHT_POSITION(3.0F, 2.0F, 3.0F);
constexpr QVector3D LIGHT_COLOR(1.0F, 0.7F, 0.7F);
constexpr QVector4D CLEAR_COLOR(0.0F, 0.5F, 1.0F, 1.0F);

constexpr float PERSPECTIVE_FOV = 60.0F;
constexpr float NEAR_PLANE = 0.1F;
constexpr float FAR_PLANE = 100.0F;

constexpr float AMBIENT_STRENGTH = 0.3F;
constexpr float SPECULAR_STRENGTH = 2.0F;
constexpr int SPECULAR_POW = 32;

constexpr float MOUSE_SENSITIVITY = 0.2F;
constexpr float ROTATION_SPEED = 30.0F;
constexpr float MOTION_SPEED = 0.1F;

constexpr QVector3D PHONG_TRANSLATION{0.0F, 1.5F, 0.0F};
constexpr QVector3D GOURAUD_TRANSLATION{0.0F, -1.5F, 0.0F};

void ThirdWindow::onMessageLogged(const QOpenGLDebugMessage &message) {
  qDebug() << message;
}

void ThirdWindow::mousePressEvent(QMouseEvent *event) {
  m_direction_input_controller->mousePressEvent(event);
}

void ThirdWindow::mouseMoveEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseMoveEvent(event);
}

void ThirdWindow::mouseReleaseEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseReleaseEvent(event);
}

void ThirdWindow::keyPressEvent(QKeyEvent *event) {
  m_motion_input_controller->keyPressEvent(event);
}

void ThirdWindow::keyReleaseEvent(QKeyEvent *event) {
  m_motion_input_controller->keyReleaseEvent(event);
}

void ThirdWindow::add_objects(
    QVector3D translation,
    const std::shared_ptr<QOpenGLShaderProgram> &program) {
  auto skull_texture =
      Resources::loadTextureShared(":/textures/skull-diffuse.jpg");

  auto cube_texture =
      Resources::loadTextureShared(":/textures/dice-diffuse.png");

  auto skull_mesh = Resources::loadMeshShared<RegularVertex, GLuint>(
      ":/models/skull.vbo-ibo", GL_TRIANGLES);

  auto cube_mesh = std::make_shared<GenericMesh<RegularVertex, GLuint>>(
      cubeVertices, cubeStripeIndices, GL_TRIANGLE_STRIP);

  FirstShader factory(program);
  auto skull_shader = factory.createShared();
  skull_shader->getParameters().setLightSource(LIGHT_POSITION + translation,
                                               LIGHT_COLOR);
  skull_shader->getParameters().setDiffuseTexture(skull_texture);
  skull_shader->getParameters().setAmbientStrength(AMBIENT_STRENGTH);
  skull_shader->getParameters().setSpecular(SPECULAR_STRENGTH, SPECULAR_POW);

  auto cube_shader = factory.createShared();
  cube_shader->setParameters(skull_shader->getParameters());
  cube_shader->getParameters().setDiffuseTexture(cube_texture);

  auto skull_rend = std::make_shared<GenericRenderable>(
      std::dynamic_pointer_cast<TypedShader<RegularVertex::Interface>>(
          skull_shader),
      std::dynamic_pointer_cast<TypedMesh<RegularVertex>>(skull_mesh));

  auto cube_rend = std::make_shared<GenericRenderable>(
      std::dynamic_pointer_cast<TypedShader<RegularVertex::Interface>>(
          cube_shader),
      std::dynamic_pointer_cast<TypedMesh<RegularVertex>>(cube_mesh));

  /*
   * Init scene objects
   */
  const QVector3D skull_scale(0.1F, 0.1F, 0.1F);
  auto skull = std::make_shared<SceneObject>();
  skull->setRenderable(skull_rend);
  skull->setScale(skull_scale);
  skull->setPosition(QVector3D(-2, 0, 0) + translation);

  auto cube = std::make_shared<SceneObject>();
  cube->setRenderable(cube_rend);
  cube->setPosition(QVector3D(2, 0, 0) + translation);

  /*
   * Init controllers
   */
  auto rotation_controller = std::make_shared<ConstantRotationController>();
  rotation_controller->setObject(skull);
  rotation_controller->setRotationSpeed(ROTATION_SPEED);
  rotation_controller->setRotationAxis({0.0F, 1.0F, 0.0F});

  /*
   * Register created objects
   */
  m_objects.push_back(skull);
  m_objects.push_back(cube);
  m_controllers.push_back(rotation_controller);
}

void ThirdWindow::init() {
  /*
   * Logger initialization
   */
  m_logger = std::make_unique<QOpenGLDebugLogger>(this);

  connect(m_logger.get(), &QOpenGLDebugLogger::messageLogged, this,
          &ThirdWindow::onMessageLogged);

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
  auto phong_program = Resources::loadShaderProgramShared(
      {":/shaders/third-phong.vert", ":/shaders/third-phong.frag",
       ":/shaders/third-common.frag"});
  add_objects(PHONG_TRANSLATION, phong_program);

  auto gouraud_program = Resources::loadShaderProgramShared(
      {":/shaders/third-gouraud.vert", ":/shaders/third-gouraud.frag",
       ":/shaders/third-common.vert"});
  add_objects(GOURAUD_TRANSLATION, gouraud_program);

  m_camera = std::make_shared<Camera>();
  m_camera->setPosition(INITIAL_CAMERA_POSITION);

  m_direction_input_controller = std::make_shared<DirectionInputController>();
  m_direction_input_controller->setObject(m_camera);
  m_direction_input_controller->setSensitivity(MOUSE_SENSITIVITY);
  m_controllers.push_back(m_direction_input_controller);

  m_motion_input_controller = std::make_shared<MotionInputController>();
  m_motion_input_controller->setObject(m_camera);
  m_motion_input_controller->setDirectionSource(m_direction_input_controller);
  m_motion_input_controller->setMotionSpeed(MOTION_SPEED);
  m_controllers.push_back(m_motion_input_controller);
}

void ThirdWindow::render() {
  const float delta = 1.0F / static_cast<float>(screen()->refreshRate());
  for (const auto &c : m_controllers) {
    c->update(delta);
  }

  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const auto pixel_ratio = devicePixelRatio();
  const auto ratio = static_cast<float>(width()) / static_cast<float>(height());
  m_camera->setPerspective(PERSPECTIVE_FOV, ratio, NEAR_PLANE, FAR_PLANE);
  m_camera->beginRender((GLsizei)(width() * pixel_ratio),
                        (GLsizei)(height() * pixel_ratio));

  for (const auto &obj : m_objects) {
    obj->render(*m_camera);
  }
}

} // namespace Kononov

#include "FourthWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <Resources.hpp>
#include <Scene/ConstantRotationController.hpp>
#include <Scene/CubeMesh.hpp>
#include <Scene/UVSphere.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>

namespace Kononov {

constexpr QVector3D INITIAL_CAMERA_POSITION(0.0F, 1.3F, 8.0F);
constexpr QVector3D LIGHT_POSITION(3.0F, 2.0F, 3.0F);
constexpr QVector3D LIGHT_COLOR(1.0F, 0.7F, 0.7F);
constexpr QVector4D CLEAR_COLOR(0.0F, 0.5F, 1.0F, 1.0F);

constexpr float AMBIENT_STRENGTH = 0.5F;
constexpr float SPECULAR_STRENGTH = 1.5F;
constexpr int SPECULAR_POW = 8;

constexpr float MOUSE_SENSITIVITY = 0.2F;
constexpr float ROTATION_SPEED = 30.0F;
constexpr float MOTION_SPEED = 0.1F;

constexpr QVector3D TRANSLATION{0.0F, 1.5F, 0.0F};

constexpr unsigned int UV_LAT_NUM = 20;
constexpr unsigned int UV_LONG_NUM = 20;

void FourthWindow::add_objects(
    QVector3D translation,
    const std::shared_ptr<QOpenGLShaderProgram> &program) {
  auto earth_diffuse =
      Resources::loadTextureShared(":/textures/earth-diffuse.jpg");
  auto earth_normal =
      Resources::loadTextureShared(":/textures/earth-normal.tif");

  auto earth_mesh = UVSphere::generateShared(UV_LAT_NUM, UV_LONG_NUM);

  FirstShader factory(program);
  auto earth_shader = factory.createShared();
  earth_shader->getParameters().setLightSource(LIGHT_POSITION + translation,
                                               LIGHT_COLOR);
  earth_shader->getParameters().setDiffuseTexture(earth_diffuse);
  earth_shader->getParameters().setAmbientStrength(AMBIENT_STRENGTH);
  earth_shader->getParameters().setSpecular(SPECULAR_STRENGTH, SPECULAR_POW);

  auto earth_rend = std::make_shared<GenericRenderable>(
      std::dynamic_pointer_cast<TypedShader<RegularVertex::Interface>>(
          earth_shader),
      std::dynamic_pointer_cast<TypedMesh<TBNVertex>>(earth_mesh));

  /*
   * Init scene objects
   */
  const QVector3D earth_scale(2.0F, 2.0F, 2.0F);
  const QVector3D earth_pos(0.0F, -1.0F, 0.0F);
  auto earth = std::make_shared<SceneObject>();
  earth->setRenderable(earth_rend);
  earth->setScale(earth_scale);
  earth->setPosition(earth_pos + translation);

  /*
   * Init controllers
   */
  auto rotation_controller = std::make_shared<ConstantRotationController>();
  rotation_controller->setObject(earth);
  rotation_controller->setRotationSpeed(ROTATION_SPEED);
  rotation_controller->setRotationAxis({0.0F, 1.0F, 0.0F});

  /*
   * Register created objects
   */
  getObjects().push_back(earth);
  getControllers().push_back(rotation_controller);
}

void FourthWindow::init() {
  SceneWindow::init();
  getCamera()->setPosition(INITIAL_CAMERA_POSITION);
  getDirectionInputController()->setSensitivity(MOUSE_SENSITIVITY);
  getMotionInputController()->setMotionSpeed(MOTION_SPEED);

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
  auto program = Resources::loadShaderProgramShared(
      {":/shaders/fourth.vert", ":/shaders/fourth.frag"});
  add_objects(TRANSLATION, program);
}

} // namespace Kononov

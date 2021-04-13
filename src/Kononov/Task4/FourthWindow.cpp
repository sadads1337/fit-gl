#include "FourthWindow.hpp"
#include "FourthShader.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <Resources.hpp>
#include <Scene/ConstantRotationController.hpp>
#include <Scene/UVSphere.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>

namespace {

const std::vector<Kononov::TBNVertex> plane_vertices{
    {{-1.0F, -1.0F, 0.0F}, {0.0F, 0.0F}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, // v0
    {{1.0F, -1.0F, 0.0F}, {1.0F, 0.0F}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}},  // v1
    {{-1.0F, 1.0F, 0.0F}, {0.0F, 1.0F}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}},  // v2
    {{1.0F, 1.0F, 0.0F}, {1.0F, 1.0F}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}},   // v3
};

const std::vector<GLuint> plane_indices{0, 1, 2, 3, 0, 1};

} // namespace

namespace Kononov {

constexpr QVector3D INITIAL_CAMERA_POSITION(0.0F, 1.3F, 8.0F);
constexpr QVector3D LIGHT_POSITION(3.0F, 2.0F, 3.0F);
constexpr QVector3D LIGHT_COLOR(1.0F, 0.7F, 0.7F);
constexpr QVector4D CLEAR_COLOR(0.0F, 0.5F, 1.0F, 1.0F);

constexpr float AMBIENT_STRENGTH = 0.5F;
constexpr float SPECULAR_STRENGTH = 1.5F;
constexpr int SPECULAR_POW = 8;

constexpr float BRICKS_AMBIENT_STRENGTH = 0.2F;
constexpr float BRICKS_SPECULAR_STRENGTH = 0.5F;
constexpr int BRICKS_SPECULAR_POW = 8;

constexpr float MOUSE_SENSITIVITY = 0.2F;
constexpr float ROTATION_SPEED = 30.0F;
constexpr float BRICKS_ROTATION_SPEED = 15.0F;
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

  auto bricks_diffuse =
      Resources::loadTextureShared(":/textures/bricks-diffuse.jpg");
  auto bricks_normal =
      Resources::loadTextureShared(":/textures/bricks-normal.jpg");

  auto earth_mesh = UVSphere::generateShared(UV_LAT_NUM, UV_LONG_NUM);
  auto bricks_mesh = std::make_shared<GenericMesh<TBNVertex, GLuint>>(
      plane_vertices, plane_indices, GL_TRIANGLE_STRIP);

  FourthShader factory(program);
  auto earth_shader = factory.createShared();
  earth_shader->getParameters().setLightSource(LIGHT_POSITION + translation,
                                               LIGHT_COLOR);
  earth_shader->getParameters().setDiffuseTexture(earth_diffuse);
  earth_shader->getParameters().setNormalTexture(earth_normal);
  earth_shader->getParameters().setAmbientStrength(AMBIENT_STRENGTH);
  earth_shader->getParameters().setSpecular(SPECULAR_STRENGTH, SPECULAR_POW);

  auto bricks_shader = factory.createShared();
  bricks_shader->getParameters().setLightSource(LIGHT_POSITION + translation,
                                                LIGHT_COLOR);
  bricks_shader->getParameters().setDiffuseTexture(bricks_diffuse);
  bricks_shader->getParameters().setNormalTexture(bricks_normal);
  bricks_shader->getParameters().setAmbientStrength(BRICKS_AMBIENT_STRENGTH);
  bricks_shader->getParameters().setSpecular(BRICKS_SPECULAR_STRENGTH,
                                             BRICKS_SPECULAR_POW);

  auto earth_rend = std::make_shared<GenericRenderable>(
      std::dynamic_pointer_cast<TypedShader<TBNVertex::Interface>>(
          earth_shader),
      std::dynamic_pointer_cast<TypedMesh<TBNVertex>>(earth_mesh));

  auto bricks_rend = std::make_shared<GenericRenderable>(
      std::dynamic_pointer_cast<TypedShader<TBNVertex::Interface>>(
          bricks_shader),
      std::dynamic_pointer_cast<TypedMesh<TBNVertex>>(bricks_mesh));

  /*
   * Init scene objects
   */
  const QVector3D earth_scale(2.0F, 2.0F, 2.0F);
  const QVector3D earth_pos(0.0F, -1.0F, 0.0F);
  auto earth = std::make_shared<SceneObject>();
  earth->setRenderable(earth_rend);
  earth->setScale(earth_scale);
  earth->setPosition(earth_pos + translation);

  const QVector3D bricks_scale(2.0F, 2.0F, 2.0F);
  const QVector3D bricks_pos(4.0F, -1.0F, 0.0F);
  auto bricks = std::make_shared<SceneObject>();
  bricks->setRenderable(bricks_rend);
  bricks->setScale(bricks_scale);
  bricks->setPosition(bricks_pos + translation);

  /*
   * Init controllers
   */
  auto rotation_controller = std::make_shared<ConstantRotationController>();
  rotation_controller->setObject(earth);
  rotation_controller->setRotationSpeed(ROTATION_SPEED);
  rotation_controller->setRotationAxis({0.0F, 1.0F, 0.0F});

  auto rotation_controller2 = std::make_shared<ConstantRotationController>();
  rotation_controller2->setObject(bricks);
  rotation_controller2->setRotationSpeed(BRICKS_ROTATION_SPEED);
  rotation_controller2->setRotationAxis({1.0F, 0.0F, 0.0F});

  /*
   * Register created objects
   */
  getObjects().push_back(earth);
  getObjects().push_back(bricks);
  getControllers().push_back(rotation_controller);
  getControllers().push_back(rotation_controller2);
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

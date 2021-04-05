#include "ThirdWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <CubeMesh.hpp>
#include <Kononov/Common/Scene/ConstantRotationController.hpp>
#include <Resources.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>

namespace Kononov {

constexpr QVector3D INITIAL_CAMERA_POSITION(0.0F, 1.3F, 8.0F);
constexpr QVector3D LIGHT_POSITION(3.0F, 2.0F, 3.0F);
constexpr QVector3D LIGHT_COLOR(1.0F, 0.7F, 0.7F);
constexpr QVector4D CLEAR_COLOR(0.0F, 0.5F, 1.0F, 1.0F);

constexpr float AMBIENT_STRENGTH = 0.3F;
constexpr float SPECULAR_STRENGTH = 2.0F;
constexpr int SPECULAR_POW = 32;

constexpr float MOUSE_SENSITIVITY = 0.2F;
constexpr float ROTATION_SPEED = 30.0F;
constexpr float MOTION_SPEED = 0.1F;

constexpr QVector3D PHONG_TRANSLATION{0.0F, 1.5F, 0.0F};
constexpr QVector3D GOURAUD_TRANSLATION{0.0F, -1.5F, 0.0F};

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
  getObjects().push_back(skull);
  getObjects().push_back(cube);
  getControllers().push_back(rotation_controller);
}

void ThirdWindow::init() {
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
  auto phong_program = Resources::loadShaderProgramShared(
      {":/shaders/third-phong.vert", ":/shaders/third-phong.frag",
       ":/shaders/third-common.frag"});
  add_objects(PHONG_TRANSLATION, phong_program);

  auto gouraud_program = Resources::loadShaderProgramShared(
      {":/shaders/third-gouraud.vert", ":/shaders/third-gouraud.frag",
       ":/shaders/third-common.vert"});
  add_objects(GOURAUD_TRANSLATION, gouraud_program);
}

} // namespace Kononov

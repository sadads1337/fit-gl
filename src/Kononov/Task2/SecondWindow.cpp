#include "SecondWindow.hpp"

#include <cmath>

#include <QOpenGLFunctions>
#include <QScreen>

#include <CubeMesh.hpp>
#include <Resources.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>

#include "SecondShader.hpp"
#include "TesselatedRenderable.hpp"

namespace Kononov {

constexpr QVector3D INITIAL_CAMERA_POSITION(0.0F, 1.3F, 8.0F);
constexpr QVector3D LIGHT_POSITION(3.0F, 2.0F, 3.0F);
constexpr QVector3D LIGHT_COLOR(1.0F, 0.7F, 0.7F);
constexpr QVector4D CLEAR_COLOR(0.0F, 0.5F, 1.0F, 1.0F);

constexpr float AMBIENT_STRENGTH = 0.3F;
constexpr float SPECULAR_STRENGTH = 0.5F;
constexpr int SPECULAR_POW = 32;

constexpr float MOUSE_SENSITIVITY = 0.2F;
constexpr float ROTATION_SPEED = 0.03F;
constexpr float ROTATION_AMPLITUDE_CUBE = 0.7F;
constexpr float ROTATION_AMPLITUDE_SKULL = 0.1F;
constexpr float MOTION_SPEED = 0.1F;

void SecondWindow::init() {
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
      cubeVertices, cubeTrianglesIndices, GL_PATCHES);

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
  auto skull = std::make_shared<SceneObject>();
  skull->setRenderable(skull_rend);
  skull->setScale(skull_scale);
  skull->setPosition(QVector3D(-2, 0, 0));
  getObjects().push_back(skull);

  auto cube = std::make_shared<SceneObject>();
  cube->setRenderable(cube_rend);
  cube->setPosition(QVector3D(2, 0, 0));
  getObjects().push_back(cube);
}

void SecondWindow::render() {
  m_cube_shader->getParameters().setSkewness(
      ROTATION_AMPLITUDE_CUBE *
      std::sin(static_cast<float>(m_frame) * ROTATION_SPEED));

  m_skull_shader->getParameters().setSkewness(
      ROTATION_AMPLITUDE_SKULL *
      std::cos(static_cast<float>(m_frame) * ROTATION_SPEED));

  m_frame++;

  SceneWindow::render();
}

} // namespace Kononov

#include "SecondShader.hpp"

#include <GLUtil.hpp>

namespace Kononov {

SecondShader::SecondShader() {
  /*
   * Shader program initialization
   */
  auto &shader = getShader();

  const char *const vertex_shader = ":/shaders/second.vs";
  const char *const fragment_shader = ":/shaders/second.fs";
  shader.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader);
  shader.addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader);
  shader.link();

  /*
   * Query locations of parameters
   */
  m_vertex_position_attr = shader.attributeLocation("vertex_position");
  m_vertex_normal_attr = shader.attributeLocation("vertex_normal");
  m_vertex_uv_attr = shader.attributeLocation("vertex_uv");

  m_model_view_matrix_uniform = shader.uniformLocation("model_view_matrix");
  m_model_matrix_uniform = shader.uniformLocation("model_matrix");
  m_normal_matrix_uniform = shader.uniformLocation("normal_matrix");

  m_diffuse_map_uniform = shader.uniformLocation("diffuse_map");
  m_ambient_strength_uniform = shader.uniformLocation("ambient_strength");
  m_specular_strength_uniform = shader.uniformLocation("specular_strength");
  m_specular_pow_uniform = shader.uniformLocation("specular_pow");
  m_light_color_uniform = shader.uniformLocation("light_color");
  m_light_pos_uniform = shader.uniformLocation("light_pos");
  m_view_pos_uniform = shader.uniformLocation("view_pos");
  m_skewness_uniform = shader.uniformLocation("skewness");
}

void SecondShader::setupCurrentVao() {
  QOpenGLShaderProgram &shader = getShader();

  constexpr auto stride = sizeof(Vertex);
  shader.setAttributeBuffer(m_vertex_position_attr, GL_FLOAT,
                            offsetof(Vertex, position), 3, stride);
  shader.setAttributeBuffer(m_vertex_normal_attr, GL_FLOAT,
                            offsetof(Vertex, normal), 3, stride);
  shader.setAttributeBuffer(m_vertex_uv_attr, GL_FLOAT, offsetof(Vertex, uv), 2,
                            stride);

  shader.enableAttributeArray(m_vertex_position_attr);
  shader.enableAttributeArray(m_vertex_uv_attr);
  shader.enableAttributeArray(m_vertex_normal_attr);
}

void SecondShader::prepare(Camera camera, QMatrix4x4 model_matrix) {
  QOpenGLShaderProgram &shader = getShader();

  shader.setUniformValue(m_view_pos_uniform, camera.getAbsolutePosition());
  shader.setUniformValue(m_model_view_matrix_uniform,
                         camera.getProjectionViewMatrix() * model_matrix);
  shader.setUniformValue(m_model_matrix_uniform, model_matrix);
  shader.setUniformValue(m_normal_matrix_uniform, model_matrix.normalMatrix());
}

void SecondShader::setParameters(SecondShaderParameters params) {
  QOpenGLShaderProgram &shader = getShader();

  shader.setUniformValue(m_diffuse_map_uniform, params.getDiffuseMap());
  shader.setUniformValue(m_ambient_strength_uniform,
                         params.getAmbientStrength());
  shader.setUniformValue(m_specular_strength_uniform,
                         params.getSpecularStrength());
  shader.setUniformValue(m_specular_pow_uniform, params.getSpecularPow());
  shader.setUniformValue(m_light_pos_uniform, params.getLightPos());
  shader.setUniformValue(m_light_color_uniform, params.getLightColor());
  shader.setUniformValue(m_skewness_uniform, params.getSkewness());
}

void SecondShaderParameters::setAmbient(GLfloat strength) {
  setAmbientStrength(strength);
}

void SecondShaderParameters::setSpecular(GLfloat strength, GLfloat pow) {
  setSpecularStrength(strength);
  setSpecularPow(pow);
}

void SecondShaderParameters::setLightSource(QVector3D pos, QVector3D color) {
  setLightPos(pos);
  setLightColor(color);
}

GLint SecondShaderParameters::getDiffuseMap() const noexcept {
  return m_diffuse_map;
}

void SecondShaderParameters::setDiffuseMap(GLint diffuse_map) {
  m_diffuse_map = diffuse_map;
}

GLfloat SecondShaderParameters::getAmbientStrength() const noexcept {
  return m_ambient_strength;
}

void SecondShaderParameters::setAmbientStrength(GLfloat ambient_strength) {
  m_ambient_strength = ambient_strength;
}

GLfloat SecondShaderParameters::getSpecularStrength() const noexcept {
  return m_specular_strength;
}

void SecondShaderParameters::setSpecularStrength(GLfloat specular_strength) {
  m_specular_strength = specular_strength;
}

GLfloat SecondShaderParameters::getSpecularPow() const noexcept {
  return m_specular_pow;
}

void SecondShaderParameters::setSpecularPow(GLfloat specular_pow) {
  m_specular_pow = specular_pow;
}

const QVector3D &SecondShaderParameters::getLightColor() const noexcept {
  return m_light_color;
}

void SecondShaderParameters::setLightColor(const QVector3D &light_color) {
  m_light_color = light_color;
}

const QVector3D &SecondShaderParameters::getLightPos() const noexcept {
  return m_light_pos;
}

void SecondShaderParameters::setLightPos(const QVector3D &light_pos) {
  m_light_pos = light_pos;
}

GLfloat SecondShaderParameters::getSkewness() const { return m_skewness; }
void SecondShaderParameters::setSkewness(GLfloat skewness) {
  m_skewness = skewness;
}

} // namespace Kononov

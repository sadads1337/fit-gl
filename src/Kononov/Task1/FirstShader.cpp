#include "FirstShader.hpp"

namespace Kononov {

FirstShader::FirstShader() {
  /*
   * Shader program initialization
   */
  const auto &shader = getShader();

  const char *const vertex_shader = ":/shaders/first.vs";
  const char *const fragment_shader = ":/shaders/first.fs";
  shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader);
  shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader);
  shader->link();

  /*
   * Query locations of parameters
   */
  m_vertex_position_attr = shader->attributeLocation("vertex_position");
  m_vertex_normal_attr = shader->attributeLocation("vertex_normal");
  m_vertex_uv_attr = shader->attributeLocation("vertex_uv");

  m_model_view_matrix_uniform = shader->uniformLocation("model_view_matrix");
  m_model_matrix_uniform = shader->uniformLocation("model_matrix");
  m_normal_matrix_uniform = shader->uniformLocation("normal_matrix");

  m_diffuse_map_uniform = shader->uniformLocation("diffuse_map");
  m_ambient_strength_uniform = shader->uniformLocation("ambient_strength");
  m_specular_strength_uniform = shader->uniformLocation("specular_strength");
  m_specular_pow_uniform = shader->uniformLocation("specular_pow");
  m_light_color_uniform = shader->uniformLocation("light_color");
  m_light_pos_uniform = shader->uniformLocation("light_pos");
  m_view_pos_uniform = shader->uniformLocation("view_pos");
}

void FirstShader::enableAttributeArrays() {
  getShader()->enableAttributeArray(m_vertex_position_attr);
  getShader()->enableAttributeArray(m_vertex_uv_attr);
  getShader()->enableAttributeArray(m_vertex_normal_attr);
}

void FirstShader::disableAttributeArrays() {
  getShader()->disableAttributeArray(m_vertex_position_attr);
  getShader()->disableAttributeArray(m_vertex_uv_attr);
  getShader()->disableAttributeArray(m_vertex_normal_attr);
}

void FirstShader::setVertexPositionBuffer(int offset, int stride) {
  getShader()->setAttributeBuffer(m_vertex_position_attr, GL_FLOAT, offset, 3,
                                  stride);
}

void FirstShader::setVertexNormalBuffer(int offset, int stride) {
  getShader()->setAttributeBuffer(m_vertex_normal_attr, GL_FLOAT, offset, 3,
                                  stride);
}

void FirstShader::setVertexUVBuffer(int offset, int stride) {
  getShader()->setAttributeBuffer(m_vertex_uv_attr, GL_FLOAT, offset, 2,
                                  stride);
}

void FirstShader::setMatrices(QMatrix4x4 view, QMatrix4x4 model) {
  getShader()->setUniformValue(FirstShader::m_model_view_matrix_uniform,
                               view * model);
  getShader()->setUniformValue(FirstShader::m_model_matrix_uniform, model);
  getShader()->setUniformValue(FirstShader::m_normal_matrix_uniform,
                               model.normalMatrix());
}

void FirstShader::setParameters(FirstShaderParameters params) {
  getShader()->setUniformValue(m_diffuse_map_uniform, params.getDiffuseMap());
  getShader()->setUniformValue(m_ambient_strength_uniform,
                               params.getAmbientStrength());
  getShader()->setUniformValue(m_specular_strength_uniform,
                               params.getSpecularStrength());
  getShader()->setUniformValue(m_specular_pow_uniform, params.getSpecularPow());
  getShader()->setUniformValue(m_light_pos_uniform, params.getLightPos());
  getShader()->setUniformValue(m_light_color_uniform, params.getLightColor());
  getShader()->setUniformValue(m_view_pos_uniform, params.getViewPos());
}

void FirstShaderParameters::setAmbient(GLfloat strength) {
  setAmbientStrength(strength);
}

void FirstShaderParameters::setSpecular(GLfloat strength, GLfloat pow) {
  setSpecularStrength(strength);
  setSpecularPow(pow);
}

void FirstShaderParameters::setLightSource(QVector3D pos, QVector3D color) {
  setLightPos(pos);
  setLightColor(color);
}

GLint FirstShaderParameters::getDiffuseMap() const noexcept {
  return m_diffuse_map;
}

void FirstShaderParameters::setDiffuseMap(GLint diffuse_map) {
  m_diffuse_map = diffuse_map;
}

GLfloat FirstShaderParameters::getAmbientStrength() const noexcept {
  return m_ambient_strength;
}

void FirstShaderParameters::setAmbientStrength(GLfloat ambient_strength) {
  m_ambient_strength = ambient_strength;
}

GLfloat FirstShaderParameters::getSpecularStrength() const noexcept {
  return m_specular_strength;
}

void FirstShaderParameters::setSpecularStrength(GLfloat specular_strength) {
  m_specular_strength = specular_strength;
}

GLfloat FirstShaderParameters::getSpecularPow() const noexcept {
  return m_specular_pow;
}

void FirstShaderParameters::setSpecularPow(GLfloat specular_pow) {
  m_specular_pow = specular_pow;
}

const QVector3D &FirstShaderParameters::getLightColor() const noexcept {
  return m_light_color;
}

void FirstShaderParameters::setLightColor(const QVector3D &light_color) {
  m_light_color = light_color;
}

const QVector3D &FirstShaderParameters::getLightPos() const noexcept {
  return m_light_pos;
}

void FirstShaderParameters::setLightPos(const QVector3D &light_pos) {
  m_light_pos = light_pos;
}

const QVector3D &FirstShaderParameters::getViewPos() const noexcept {
  return m_view_pos;
}

void FirstShaderParameters::setViewPos(const QVector3D &view_pos) {
  m_view_pos = view_pos;
}

} // namespace Kononov

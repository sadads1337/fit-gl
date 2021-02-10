#include "FirstShader.hpp"

namespace Kononov {

FirstShader::FirstShader()
    : m_vertex_position_attr(0), m_vertex_normal_attr(0), m_vertex_uv_attr(0),
      m_view_matrix_uniform(0), m_model_matrix_uniform(0),
      m_normal_matrix_uniform(0), m_diffuse_map_uniform(0),
      m_ambient_strength_uniform(0), m_specular_strength_uniform(0),
      m_specular_pow_uniform(0), m_light_color_uniform(0),
      m_light_pos_uniform(0), m_view_pos_uniform(0) {
  /*
   * Shader program initialization
   */
  m_shader = std::make_unique<QOpenGLShaderProgram>();
  m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/shaders/first.vs");
  m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/shaders/first.fs");
  m_shader->link();

  /*
   * Query locations of parameters
   */
  m_vertex_position_attr = m_shader->attributeLocation("vertex_position");
  m_vertex_normal_attr = m_shader->attributeLocation("vertex_normal");
  m_vertex_uv_attr = m_shader->attributeLocation("vertex_uv");

  m_view_matrix_uniform = m_shader->uniformLocation("view_matrix");
  m_model_matrix_uniform = m_shader->uniformLocation("model_matrix");
  m_normal_matrix_uniform = m_shader->uniformLocation("normal_matrix");

  m_diffuse_map_uniform = m_shader->uniformLocation("diffuse_map");
  m_ambient_strength_uniform = m_shader->uniformLocation("ambient_strength");
  m_specular_strength_uniform = m_shader->uniformLocation("specular_strength");
  m_specular_pow_uniform = m_shader->uniformLocation("specular_pow");
  m_light_color_uniform = m_shader->uniformLocation("light_color");
  m_light_pos_uniform = m_shader->uniformLocation("light_pos");
  m_view_pos_uniform = m_shader->uniformLocation("view_pos");
}

void FirstShader::bind() { m_shader->bind(); }

void FirstShader::release() { m_shader->release(); }

void FirstShader::enableAttributeArrays() {
  m_shader->enableAttributeArray(m_vertex_position_attr);
  m_shader->enableAttributeArray(m_vertex_uv_attr);
  m_shader->enableAttributeArray(m_vertex_normal_attr);
}

void FirstShader::disableAttributeArrays() {
  m_shader->disableAttributeArray(m_vertex_position_attr);
  m_shader->disableAttributeArray(m_vertex_uv_attr);
  m_shader->disableAttributeArray(m_vertex_normal_attr);
}

void FirstShader::setVertexPositionBuffer(int offset, int stride) {
  m_shader->setAttributeBuffer(m_vertex_position_attr, GL_FLOAT, offset, 3,
                               stride);
}

void FirstShader::setVertexNormalBuffer(int offset, int stride) {
  m_shader->setAttributeBuffer(m_vertex_normal_attr, GL_FLOAT, offset, 3,
                               stride);
}

void FirstShader::setVertexUVBuffer(int offset, int stride) {
  m_shader->setAttributeBuffer(m_vertex_uv_attr, GL_FLOAT, offset, 2, stride);
}

void FirstShader::setMatrices(QMatrix4x4 view, QMatrix4x4 model) {
  m_shader->setUniformValue(m_view_matrix_uniform, view);
  m_shader->setUniformValue(m_model_matrix_uniform, model);
  m_shader->setUniformValue(m_normal_matrix_uniform, model.normalMatrix());
}

void FirstShader::setDiffuseMap(GLint unit) {
  m_shader->setUniformValue(m_diffuse_map_uniform, unit);
}

void FirstShader::setAmbient(GLfloat strength) {
  m_shader->setUniformValue(m_ambient_strength_uniform, strength);
}

void FirstShader::setSpecular(GLfloat strength, GLfloat pow) {
  m_shader->setUniformValue(m_specular_strength_uniform, strength);
  m_shader->setUniformValue(m_specular_pow_uniform, pow);
}

void FirstShader::setLightSource(QVector3D pos, QVector3D color) {
  m_shader->setUniformValue(m_light_pos_uniform, pos);
  m_shader->setUniformValue(m_light_color_uniform, color);
}

void FirstShader::setViewPosition(QVector3D pos) {
  m_shader->setUniformValue(m_view_pos_uniform, pos);
}

} // namespace Kononov

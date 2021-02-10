#pragma once

#include <memory>

#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>

namespace Kononov {

class FirstShader {
public:
  FirstShader();

  void bind();
  void release();

  void enableAttributeArrays();
  void disableAttributeArrays();

  void setVertexPositionBuffer(int offset, int stride);
  void setVertexNormalBuffer(int offset, int stride);
  void setVertexUVBuffer(int offset, int stride);

  void setMatrices(QMatrix4x4 view, QMatrix4x4 model);

  void setDiffuseMap(GLint unit);
  void setAmbient(GLfloat strength);
  void setSpecular(GLfloat strength, GLfloat pow);
  void setLightSource(QVector3D pos, QVector3D color);
  void setViewPosition(QVector3D pos);

private:
  GLint m_vertex_position_attr = 0;
  GLint m_vertex_normal_attr = 0;
  GLint m_vertex_uv_attr = 0;

  GLint m_view_matrix_uniform = 0;
  GLint m_model_matrix_uniform = 0;
  GLint m_normal_matrix_uniform = 0;

  GLint m_diffuse_map_uniform = 0;
  GLint m_ambient_strength_uniform = 0;
  GLint m_specular_strength_uniform = 0;
  GLint m_specular_pow_uniform = 0;
  GLint m_light_color_uniform = 0;
  GLint m_light_pos_uniform = 0;
  GLint m_view_pos_uniform = 0;

  std::unique_ptr<QOpenGLShaderProgram> m_shader;
};

} // namespace Kononov

#pragma once

#include <memory>

#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>

#include <ShaderProgram.hpp>

#include "Vertex.hpp"

namespace Kononov {

class FirstShaderParameters;

class FirstShader : public ShaderProgram<Vertex> {
public:
  FirstShader();

  void setupCurrentVao() override;

  void setMatrices(QMatrix4x4 view, QMatrix4x4 model) override;

  void setParameters(FirstShaderParameters params);

private:
  GLint m_vertex_position_attr;
  GLint m_vertex_normal_attr;
  GLint m_vertex_uv_attr;

  GLint m_model_view_matrix_uniform;
  GLint m_model_matrix_uniform;
  GLint m_normal_matrix_uniform;

  GLint m_diffuse_map_uniform;
  GLint m_ambient_strength_uniform;
  GLint m_specular_strength_uniform;
  GLint m_specular_pow_uniform;
  GLint m_light_color_uniform;
  GLint m_light_pos_uniform;
  GLint m_view_pos_uniform;
};

class FirstShaderParameters {
public:
  void setAmbient(GLfloat strength);
  void setSpecular(GLfloat strength, GLfloat pow);
  void setLightSource(QVector3D pos, QVector3D color);

  [[nodiscard]] GLint getDiffuseMap() const noexcept;
  void setDiffuseMap(GLint diffuse_map);
  [[nodiscard]] GLfloat getAmbientStrength() const noexcept;
  void setAmbientStrength(GLfloat ambient_strength);
  [[nodiscard]] GLfloat getSpecularStrength() const noexcept;
  void setSpecularStrength(GLfloat specular_strength);
  [[nodiscard]] GLfloat getSpecularPow() const noexcept;
  void setSpecularPow(GLfloat specular_pow);
  [[nodiscard]] const QVector3D &getLightColor() const noexcept;
  void setLightColor(const QVector3D &light_color);
  [[nodiscard]] const QVector3D &getLightPos() const noexcept;
  void setLightPos(const QVector3D &light_pos);
  [[nodiscard]] const QVector3D &getViewPos() const noexcept;
  void setViewPos(const QVector3D &view_pos);

private:
  GLint m_diffuse_map;
  GLfloat m_ambient_strength;
  GLfloat m_specular_strength;
  GLfloat m_specular_pow;
  QVector3D m_light_color;
  QVector3D m_light_pos;
  QVector3D m_view_pos;
};

} // namespace Kononov

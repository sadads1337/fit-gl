#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <Shader.hpp>

#include "Camera.hpp"
#include "Vertex.hpp"

namespace Kononov {

template <typename Base> struct FirstShaderMeta {
  using VertexInterface = RegularVertex::Interface;

  struct Data : Base::Data {
    GLint vertex_position_attr;
    GLint vertex_normal_attr;
    GLint vertex_uv_attr;

    GLint model_view_matrix;
    GLint model_matrix;
    GLint normal_matrix;

    GLint diffuse_map;
    GLint ambient_strength;
    GLint specular_strength;
    GLint specular_pow;
    GLint light_color;
    GLint light_pos;
    GLint view_pos;
  };

  static void initData(const QOpenGLShaderProgram &p, Data &d) {
    d.vertex_position_attr = p.attributeLocation("vertex_position");
    d.vertex_normal_attr = p.attributeLocation("vertex_normal");
    d.vertex_uv_attr = p.attributeLocation("vertex_uv");

    d.model_view_matrix = p.uniformLocation("model_view_matrix");
    d.model_matrix = p.uniformLocation("model_matrix");
    d.normal_matrix = p.uniformLocation("normal_matrix");

    d.diffuse_map = p.uniformLocation("diffuse_map");
    d.ambient_strength = p.uniformLocation("ambient_strength");
    d.specular_strength = p.uniformLocation("specular_strength");
    d.specular_pow = p.uniformLocation("specular_pow");
    d.light_color = p.uniformLocation("light_color");
    d.light_pos = p.uniformLocation("light_pos");
    d.view_pos = p.uniformLocation("view_pos");
  }

  class Parameters : public Base::Parameters {
  private:
    std::shared_ptr<QOpenGLTexture> m_diffuse_texture;
    GLfloat m_ambient_strength;
    GLfloat m_specular_strength;
    GLfloat m_specular_pow;
    QVector3D m_light_color;
    QVector3D m_light_pos;

  public:
    void setSpecular(GLfloat strength, GLfloat pow) {
      m_specular_strength = strength;
      m_specular_pow = pow;
    }
    void setLightSource(QVector3D pos, QVector3D color) {
      m_light_pos = pos;
      m_light_color = color;
    }

    [[nodiscard]] std::shared_ptr<QOpenGLTexture> getDiffuseTexture() const {
      return m_diffuse_texture;
    }
    void setDiffuseTexture(std::shared_ptr<QOpenGLTexture> diffuse_texture) {
      m_diffuse_texture = std::move(diffuse_texture);
    }
    [[nodiscard]] GLfloat getAmbientStrength() const {
      return m_ambient_strength;
    }
    void setAmbientStrength(GLfloat ambient_strength) {
      m_ambient_strength = ambient_strength;
    }
    [[nodiscard]] GLfloat getSpecularStrength() const {
      return m_specular_strength;
    }
    void setSpecularStrength(GLfloat specular_strength) {
      m_specular_strength = specular_strength;
    }
    [[nodiscard]] GLfloat getSpecularPow() const { return m_specular_pow; }
    void setSpecularPow(GLfloat specular_pow) { m_specular_pow = specular_pow; }
    [[nodiscard]] const QVector3D &getLightColor() const {
      return m_light_color;
    }
    void setLightColor(const QVector3D &light_color) {
      m_light_color = light_color;
    }
    [[nodiscard]] const QVector3D &getLightPos() const { return m_light_pos; }
    void setLightPos(const QVector3D &light_pos) { m_light_pos = light_pos; }
  };

  static void initVertexArray(QOpenGLShaderProgram &program, const Data &data,
                              const VertexInterface &mapper) {
    auto stride = mapper.getStride();

    program.enableAttributeArray(data.vertex_position_attr);
    program.setAttributeBuffer(data.vertex_position_attr, GL_FLOAT,
                               mapper.getPositionOffset(), 3, stride);

    program.enableAttributeArray(data.vertex_normal_attr);
    program.setAttributeBuffer(data.vertex_normal_attr, GL_FLOAT,
                               mapper.getNormalOffset(), 3, stride);

    program.enableAttributeArray(data.vertex_uv_attr);
    program.setAttributeBuffer(data.vertex_uv_attr, GL_FLOAT,
                               mapper.getUVOffset(), 2, stride);
  }

  static void prepare(const Camera &camera, const QMatrix4x4 &model_matrix,
                      QOpenGLShaderProgram &program, const Data &data,
                      const Parameters &params) {
    // Set camera parameters
    program.setUniformValue(data.view_pos, camera.getAbsolutePosition());
    program.setUniformValue(data.model_view_matrix,
                            camera.getProjectionViewMatrix() * model_matrix);
    program.setUniformValue(data.model_matrix, model_matrix);
    program.setUniformValue(data.normal_matrix, model_matrix.normalMatrix());

    // Set other parameters
    params.getDiffuseTexture()->bind(0);
    program.setUniformValue(data.diffuse_map, 0);
    program.setUniformValue(data.ambient_strength, params.getAmbientStrength());
    program.setUniformValue(data.specular_strength,
                            params.getSpecularStrength());
    program.setUniformValue(data.specular_pow, params.getSpecularPow());
    program.setUniformValue(data.light_pos, params.getLightPos());
    program.setUniformValue(data.light_color, params.getLightColor());
  }

  // NOLINTNEXTLINE(hicpp-named-parameter, readability-named-parameter)
  static void cleanup(QOpenGLShaderProgram &, const Data &,
                      const Parameters &params) {
    params.getDiffuseTexture()->release();
  }
};

using FirstShader = MakeShader<FirstShaderMeta>;

} // namespace Kononov
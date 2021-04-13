#pragma once

#include <memory>

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <Shader.hpp>

#include <FirstShader.hpp>

#include "Camera.hpp"
#include "Vertex.hpp"

namespace Kononov {

template <typename Base> struct FourthShaderMeta {
  using VertexInterface = TBNVertex::Interface;

  struct Data : Base::Data {
    GLint vertex_tangent_attr;
    GLint vertex_bitangent_attr;
    GLint normal_map;
  };

  static void initData(const QOpenGLShaderProgram &p, Data &d) {
    d.normal_map = p.uniformLocation("normal_map");
    d.vertex_tangent_attr = p.attributeLocation("vertex_tangent");
    d.vertex_bitangent_attr = p.attributeLocation("vertex_bitangent");
  }

  class Parameters : public Base::Parameters {
  private:
    std::shared_ptr<QOpenGLTexture> m_normal_texture;

  public:
    [[nodiscard]] std::shared_ptr<QOpenGLTexture> getNormalTexture() const {
      return m_normal_texture;
    }
    void setNormalTexture(std::shared_ptr<QOpenGLTexture> normal_texture) {
      m_normal_texture = std::move(normal_texture);
    }
  };

  static void initVertexArray(QOpenGLShaderProgram &program, const Data &data,
                              const VertexInterface &mapper) {
    auto stride = mapper.getStride();

    program.enableAttributeArray(data.vertex_tangent_attr);
    program.setAttributeBuffer(data.vertex_tangent_attr, GL_FLOAT,
                               mapper.getTangentOffset(), 3, stride);

    program.enableAttributeArray(data.vertex_bitangent_attr);
    program.setAttributeBuffer(data.vertex_bitangent_attr, GL_FLOAT,
                               mapper.getBitangentOffset(), 3, stride);
  }

  static void prepare(QOpenGLShaderProgram &program, const Data &data,
                      const Parameters &params) {
    params.getNormalTexture()->bind(1);
    program.setUniformValue(data.normal_map, 1);
  }
};

using FourthShader = MakeShader<FourthShaderMeta, FirstShader>;

} // namespace Kononov
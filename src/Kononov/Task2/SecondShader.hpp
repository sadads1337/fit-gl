#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <Shader.hpp>

#include <FirstShader.hpp>

#include "Camera.hpp"
#include "Vertex.hpp"

namespace Kononov {

template <typename Base> struct SecondShaderMeta {
  using VertexInterface = RegularVertex::Interface;

  struct Data : Base::Data {
    GLint skewness;
  };

  static void initData(const QOpenGLShaderProgram &p, Data &d) {
    d.skewness = p.uniformLocation("skewness");
  }

  class Parameters : public Base::Parameters {
  private:
    GLfloat m_skewness;

  public:
    [[nodiscard]] GLfloat getSkewness() const { return m_skewness; };
    void setSkewness(GLfloat skewness) { m_skewness = skewness; };
  };

  static void prepare(QOpenGLShaderProgram &program, const Data &data,
                      const Parameters &params) {
    program.setUniformValue(data.skewness, params.getSkewness());
  }
};

using SecondShader = MakeShader<SecondShaderMeta, FirstShader>;

} // namespace Kononov
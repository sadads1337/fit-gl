#pragma once

#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>

#include <memory>

namespace Kononov {

class ShaderProgram {
private:
  std::unique_ptr<QOpenGLShaderProgram> m_shader;

protected:
  [[nodiscard]] QOpenGLShaderProgram &getShader() const noexcept;

public:
  ShaderProgram();
  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram(ShaderProgram &&) = default;
  virtual ~ShaderProgram() = default;
  ShaderProgram &operator=(const ShaderProgram &) = delete;
  ShaderProgram &operator=(ShaderProgram &&) = default;

  void bind();
  void release();
  virtual void setMatrices(QMatrix4x4 view, QMatrix4x4 model) = 0;
};

} // namespace Kononov

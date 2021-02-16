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
  [[nodiscard]] const std::unique_ptr<QOpenGLShaderProgram> &getShader() const noexcept;

public:
  ShaderProgram();

  void bind();
  void release();
  virtual void setMatrices(QMatrix4x4 view, QMatrix4x4 model) = 0;
};

} // namespace Kononov

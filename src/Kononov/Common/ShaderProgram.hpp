#pragma once

#include <memory>
#include <vector>

#include <QOpenGLShaderProgram>
#include <QString>
#include <QVector3D>
#include <QVector4D>

#include "Camera.hpp"

namespace Kononov {

class ShaderProgramBase {
private:
  std::unique_ptr<QOpenGLShaderProgram> m_shader;

protected:
  explicit ShaderProgramBase(const std::vector<QString> &files);

  [[nodiscard]] QOpenGLShaderProgram &getShader() const noexcept;
  [[nodiscard]] GLint getAttributeLocation(const QString &name) const;
  [[nodiscard]] GLint getUniformLocation(const QString &name) const;

public:
  ShaderProgramBase(const ShaderProgramBase &) = delete;
  ShaderProgramBase(ShaderProgramBase &&) noexcept = default;
  virtual ~ShaderProgramBase() = default;
  ShaderProgramBase &operator=(const ShaderProgramBase &) = delete;
  ShaderProgramBase &operator=(ShaderProgramBase &&) noexcept = default;

  virtual void setupCurrentVao() = 0;
  virtual void prepare(Camera camera, QMatrix4x4 model_matrix) = 0;

  void bind() { m_shader->bind(); }
  void release() { m_shader->release(); }
};

template <typename TVertex> class ShaderProgram : public ShaderProgramBase {
public:
  using ShaderProgramBase::ShaderProgramBase;
};

} // namespace Kononov

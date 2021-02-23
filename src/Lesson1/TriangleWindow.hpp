#pragma once

#include <Base/GLWindow.hpp>

#include <memory>

#include <QOpenGLShaderProgram>

namespace fgl {

class TriangleWindow final : public GLWindow {
public:
  void init() override;
  void render() override;

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colAttr_ = 0;
  GLint matrixUniform_ = 0;

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;
};

} // namespace fgl
#pragma once

#include <Base/GLWindow.hpp>
#include <QColorDialog>
#include <QMouseEvent>

#include <memory>

#include <QOpenGLShaderProgram>

namespace fgl {

class CubeWindow final : public GLWindow {
public:
  void init() override;
  void render() override;

  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colorUniform_ = 0;
  GLint matrixUniform_ = 0;

  unsigned int vertex_buffer = 0;
  unsigned int ibo = 0;

  QVector4D color{1.0f, 0.0f, 1.0f, 0.2f};

  QVector2D mousePressPosition;
  QVector3D rotationAxis{0.0f, 1.0f, 0.0f};

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;
};

} // namespace fgl
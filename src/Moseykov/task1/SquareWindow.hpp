#pragma once

#include <Base/GLWindow.hpp>
#include <memory>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QKeyEvent>
#include <QColor>
#include <QColorDialog>

namespace fgl {

class SquareWindow final : public GLWindow {
public:
  void init() override;
  void render() override;

private:

  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *event) override;

  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint matrixUniform_ = 0;

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  QOpenGLBuffer array_buffer_;
  QOpenGLBuffer index_buffer_{QOpenGLBuffer::IndexBuffer};

  QVector4D square_color{1.0, 1.0, 1.0, 1};
  QVector2D mousePressPosition{0., 0.};
  QVector3D rotationAxis{0., 0., 1.};



};

} // namespace fgl
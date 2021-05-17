#pragma once

#include <Base/GLWindow.hpp>

#include <memory>
#include <chrono>
#include <ctime>

#include <QOpenGLShaderProgram>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

namespace fgl {

class CubeWindow final : public GLWindow {

public:
  void init() override;
  void render() override;

private:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colAttr_ = 0;
  GLint norm_ = 0;
  GLint matrixUniform_ = 0;
  GLint modelUniform_ = 0;

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo{QOpenGLBuffer::IndexBuffer};

  QVector4D cube_color{1.0, 1.0, 1.0, 1};


  QVector2D mousePressPosition{0.0, 0.0};
  QVector3D rotationAxis = QVector3D(0.0, 1.0, 0.0).normalized();
  
};

} // namespace fgl
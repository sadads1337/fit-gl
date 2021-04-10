#pragma once

#include <Base/GLWindow.hpp>

#include <chrono>
#include <ctime>
#include <memory>

#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>

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
  GLint matrixUniform_ = 0;
  GLint colAttr_ = 0;

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo{QOpenGLBuffer::IndexBuffer};

  QVector4D cube_color{1.0, 1.0, 1.0, 1};

  std::chrono::duration<float> time_;
  std::chrono::time_point<std::chrono::system_clock> start;

  QVector2D mousePressPosition{0.0, 0.0};
  QVector3D rotationAxis = QVector3D(0.0, 1.0, 0.0).normalized();
};

} // namespace fgl
#pragma once

#include <Base/GLWindow.hpp>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <memory>
#include <chrono>
#include <ctime>

class CubeWindow final : public fgl::GLWindow {

public:
  void init() override;
  void render() override;

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *event) override;

  void initCube(float width, int N);

private:
  GLint posAttr_ = 0;
  GLint matrixUniform_ = 0;

  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo{QOpenGLBuffer::Type::IndexBuffer};

  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  QVector4D changeColor{0.5, 0.0, 1.0, 1};

  int frame_ = 0;

  std::chrono::duration<float> time_;
  std::chrono::time_point<std::chrono::system_clock> start;

  QVector2D mousePressPosition{0., 0.};
  QVector3D rotationAxis = QVector3D(0.0, 1.0, 0.0).normalized();
};

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

class CubeWindow final : public fgl::GLWindow {

public:
  void init() override;
  void render() override;

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  GLint posAttr_ = 0;
  GLint matrixUniform_ = 0;

  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo{QOpenGLBuffer::Type::IndexBuffer};

  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  QVector4D changeColor{0.0, 1.0, 1.0, 1};

  int frame_ = 0;

  QVector2D mousePressPosition{0., 0.};
  QVector3D rotationAxis{0., 0., 1.};
};

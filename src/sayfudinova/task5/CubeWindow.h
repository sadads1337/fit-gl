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

namespace fgl {

class CubeWindow final : public fgl::GLWindow {

public:
  void init() override;
  void render() override;

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  GLint posAttr_ = 0;
  GLint matrixUniform_ = 0;
  GLint norm_ = 0;
  GLint modelUniform_ = 0;

  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};

  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  QVector4D changeColor_{1.0f, 0.0f, 0.3f, 1};

  int frame_ = 0;

  QVector2D mousePressPosition_{0., 0.};
  QVector3D rotationAxis_ = QVector3D(0.0f, 1.0f, 0.0f).normalized();
};

} // namespace fgl
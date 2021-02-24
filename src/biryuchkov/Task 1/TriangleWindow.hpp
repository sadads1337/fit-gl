#pragma once

#include <Base/GLWindow.hpp>

#include <QOpenGLShaderProgram>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>



namespace fgl {

class TriangleWindow final : public GLWindow {
public:
  void init() override;
  void render() override;
  ~TriangleWindow();

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
 // void timerEvent(QTimerEvent *e) override;

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colAttr_ = 0;
  GLint matrixUniform_ = 0;
  qreal angularSpeed = 0;
  QQuaternion rotation;
  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  //animation
  QVector2D mousePressPosition;
  QVector3D rotationAxis;
};

} // namespace fgl
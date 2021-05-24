#pragma once

#include <Base/GLWindow.hpp>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
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
  void initCube(float width, int N);
  void initText();

private:
  GLint posAttr_ = 0;
  GLint normAttr_ = 0;
  GLint textureAttr_ = 0;
  GLint tangentAttr_ = 0;

  std::shared_ptr<QOpenGLTexture> texture_ = nullptr;
  std::shared_ptr<QOpenGLTexture> normalMap_ = nullptr;

  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};

  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  int frame_ = 0;

  QVector2D mousePressPosition_{0., 0.};
  QVector3D rotationAxis_ = QVector3D(0.0f, 1.0f, 0.0f).normalized();
};

} // namespace fgl
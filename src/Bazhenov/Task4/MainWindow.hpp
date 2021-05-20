#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "Base/GLWindow.hpp"

#include "InputController/InputController.hpp"

namespace Bazhenov {

struct VertexData {
  QVector3D position;
  QVector3D normal;

  QVector2D texture;

  QVector3D tangent;
  QVector3D bitangent;
};

class MainWindow final : public fgl::GLWindow {
  Q_OBJECT
public:
  void init() override;
  void render() override;

protected:
  void initShaders();
  void initCube(GLfloat halfWidth, std::uint32_t factor = 1U);
  void initTextures();

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

private:
  std::unique_ptr<QOpenGLShaderProgram> program_;

  QOpenGLBuffer arrayBuf_;
  QOpenGLBuffer indexBuf_{QOpenGLBuffer::IndexBuffer};

  std::shared_ptr<InputController> inputController_;

  std::unique_ptr<QOpenGLTexture> texture_;
  std::unique_ptr<QOpenGLTexture> normalMap_;

  std::uint32_t frame_ = 0;
};

} // namespace Bazhenov

#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "Base/GLWindow.hpp"

#include "InputController/InputController.hpp"

namespace Bazhenov {

class MainWindow final : public fgl::GLWindow {
  Q_OBJECT
public:
  void init() override;
  void render() override;

protected:
  void initShaders();

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

  std::uint32_t frame_ = 0;
};

} // namespace Bazhenov

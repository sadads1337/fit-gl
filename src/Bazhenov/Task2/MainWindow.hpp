#ifndef BAZHENOV_TASK2_MAINWINDOW_HPP
#define BAZHENOV_TASK2_MAINWINDOW_HPP

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
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

private:
  std::unique_ptr<QOpenGLShaderProgram> program_;

  GLint posAttr_ = 0;
  GLint colAttr_ = 0;
  GLint matrixUniform_ = 0;

  QOpenGLBuffer arrayBuf_;
  QOpenGLBuffer indexBuf_{QOpenGLBuffer::IndexBuffer};

  std::shared_ptr<InputController> inputController_;
};

} // namespace Bazhenov

#endif // BAZHENOV_TASK2_MAINWINDOW_HPP

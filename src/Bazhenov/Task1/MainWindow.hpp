#ifndef BAZHENOV_TASK1_MAINWINDOW_HPP
#define BAZHENOV_TASK1_MAINWINDOW_HPP

#include "Base/GLWindow.hpp"

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
  int frame_ = 0;
};

}

#endif // BAZHENOV_TASK1_MAINWINDOW_HPP

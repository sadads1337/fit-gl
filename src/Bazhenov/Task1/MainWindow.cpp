#include "MainWindow.hpp"

#include <QVector4D>

namespace Bazhenov {

constexpr QVector4D CLEAR_COLOR(0, 0.5, 1, 1);

void MainWindow::init() {
  // Configure OpenGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(), CLEAR_COLOR.w());

  // Load and configure shaders
}

void MainWindow::render() {
  GLWindow::render();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  QWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  QWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  QWindow::mouseReleaseEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  QWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  QWindow::keyReleaseEvent(event);
}

}
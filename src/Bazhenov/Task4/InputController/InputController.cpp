#include "InputController.hpp"

namespace Bazhenov {

QQuaternion InputController::getRotation() const noexcept {
  return rotation_;
}

QColor InputController::getColor() const noexcept {
  return color_;
}

InputController::Shader InputController::getShader() const noexcept {
  return currentShader_;
}

bool InputController::morphingIsOn() const noexcept {
  return morphingOn_;
}

bool InputController::lightIsOrbiting() const noexcept {
  return orbitingOn_;
}

void InputController::mousePressEvent(QMouseEvent *event){
  mousePosition_ = event->pos();

  pressedMouseButtons_.setFlag(event->button(), true);
}

void InputController::mouseMoveEvent(QMouseEvent *event){
  if (pressedMouseButtons_.testFlag(Qt::LeftButton)) {
    handleMove(event->pos());
  }
}

void InputController::mouseReleaseEvent(QMouseEvent *event){
  if (pressedMouseButtons_.testFlag(Qt::LeftButton)) {
    handleMove(event->pos());
  }

  pressedMouseButtons_.setFlag(event->button(), false);
}

void InputController::keyPressEvent(QKeyEvent *event){
  pressedKeys_.insert(static_cast<Qt::Key>(event->key()));
}

void InputController::keyReleaseEvent(QKeyEvent *event){
  pressedKeys_.erase(static_cast<Qt::Key>(event->key()));
}

void InputController::update() {
  if (!!pressedKeys_.count(Qt::Key::Key_G)) {
    currentShader_ = Shader::SHADER_GOURAUD;
    pressedKeys_.erase(Qt::Key::Key_G);
  }

  if (!!pressedKeys_.count(Qt::Key::Key_P)) {
    currentShader_ = Shader::SHADER_PHONG;
    pressedKeys_.erase(Qt::Key::Key_P);
  }

  if (!!pressedKeys_.count(Qt::Key::Key_M)) {
    morphingOn_ = !morphingOn_;
    pressedKeys_.erase(Qt::Key::Key_M);
  }

  if (!!pressedKeys_.count(Qt::Key::Key_O)) {
    orbitingOn_ = !orbitingOn_;
    pressedKeys_.erase(Qt::Key::Key_O);
  }
}

bool InputController::destructiveCheckNewColorSelected() {
  bool res = newColorSelected_;
  newColorSelected_ = false;
  return res;
}

void InputController::handleMove(QPoint newPosition) {
  const auto diff = QVector2D{newPosition - mousePosition_};

  const auto axis = QVector3D{diff.y(), diff.x(), 0.0F}.normalized();
  const auto angle = diff.length() * sensitivity_;

  rotation_ = QQuaternion::fromAxisAndAngle(axis, angle) * rotation_;

  mousePosition_ = newPosition;
}

}
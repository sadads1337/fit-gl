#include "InputController.hpp"

namespace Bazhenov {

QQuaternion InputController::getRotation() const noexcept {
  return rotation_;
}

QColor InputController::getColor() const noexcept {
  return color_;
}

void InputController::mousePressEvent(QMouseEvent *event){
  mousePosition_ = event->pos();

  pressedMouseButtons_.insert(event->button());
}

void InputController::mouseMoveEvent(QMouseEvent *event){
  if (!!pressedMouseButtons_.count(Qt::LeftButton)) {
    handleMove(event->pos());
  }
}

void InputController::mouseReleaseEvent(QMouseEvent *event){
  if (!!pressedMouseButtons_.count(Qt::LeftButton)) {
    handleMove(event->pos());
  }

  pressedMouseButtons_.erase(event->button());
}

void InputController::keyPressEvent(QKeyEvent *event){
  pressedKeys_.insert(static_cast<Qt::Key>(event->key()));
}

void InputController::keyReleaseEvent(QKeyEvent *event){
  pressedKeys_.erase(static_cast<Qt::Key>(event->key()));
}

void InputController::update() {
  if (!!pressedKeys_.count(Qt::Key::Key_Space)) {
    const auto color = QColorDialog::getColor(Qt::black, nullptr, "Select color");

    if (color.isValid()) {
      color_ = color;
      newColorSelected_ = true;
    }

    pressedKeys_.erase(Qt::Key::Key_Space);
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
#include "MotionInputController.hpp"

namespace Kononov {

void MotionInputController::keyPressEvent(QKeyEvent *event) {
  m_pressed_keys.insert(event->key());
}

void MotionInputController::keyReleaseEvent(QKeyEvent *event) {
  m_pressed_keys.erase(event->key());
}

void MotionInputController::update() {
  if (m_object == nullptr || m_direction_source == nullptr) {
    return;
  }
  QVector3D pos = m_object->getPosition();

  QVector3D hor_direction;
  QVector3D vert_direction;
  if (m_pressed_keys.find(Qt::Key::Key_W) != m_pressed_keys.end()) {
    hor_direction += m_direction_source->getWalkDirection();
  }
  if (m_pressed_keys.find(Qt::Key::Key_S) != m_pressed_keys.end()) {
    hor_direction -= m_direction_source->getWalkDirection();
  }
  if (m_pressed_keys.find(Qt::Key::Key_A) != m_pressed_keys.end()) {
    hor_direction -= m_direction_source->getRightDirection();
  }
  if (m_pressed_keys.find(Qt::Key::Key_D) != m_pressed_keys.end()) {
    hor_direction += m_direction_source->getRightDirection();
  }

  if (m_pressed_keys.find(Qt::Key::Key_Space) != m_pressed_keys.end()) {
    vert_direction += m_direction_source->getUpDirection();
  }
  if (m_pressed_keys.find(Qt::Key::Key_Shift) != m_pressed_keys.end()) {
    vert_direction -= m_direction_source->getUpDirection();
  }

  pos += m_motion_speed * hor_direction.normalized();
  pos += m_motion_speed * vert_direction;

  m_object->setPosition(pos);
}

const std::shared_ptr<PositionedObject> &
MotionInputController::getObject() const noexcept {
  return m_object;
}

void MotionInputController::setObject(
    const std::shared_ptr<PositionedObject> &object) {
  m_object = object;
}

const std::shared_ptr<DirectionInputController> &
MotionInputController::getDirectionSource() const noexcept {
  return m_direction_source;
}

void MotionInputController::setDirectionSource(
    const std::shared_ptr<DirectionInputController> &direction_source) {
  m_direction_source = direction_source;
}

float MotionInputController::getMotionSpeed() const noexcept {
  return m_motion_speed;
}

void MotionInputController::setMotionSpeed(float motion_speed) {
  m_motion_speed = motion_speed;
}

} // namespace Kononov

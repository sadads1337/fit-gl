#include "MotionInputController.hpp"

#include <utility>

namespace Kononov {

MotionInputController::MotionInputController(
    std::shared_ptr<DirectionInputController> look_dir)
    : m_look_dir(std::move(look_dir)) {}

void MotionInputController::keyPressEvent(QKeyEvent *event) {
  m_pressed_keys.insert(event->key());
}

void MotionInputController::keyReleaseEvent(QKeyEvent *event) {
  m_pressed_keys.erase(event->key());
}

void MotionInputController::update() {
  QVector3D hor_direction;
  QVector3D vert_direction;
  if (m_pressed_keys.find(Qt::Key::Key_W) != m_pressed_keys.end())
    hor_direction += m_look_dir->getWalkDirection();
  if (m_pressed_keys.find(Qt::Key::Key_S) != m_pressed_keys.end())
    hor_direction -= m_look_dir->getWalkDirection();
  if (m_pressed_keys.find(Qt::Key::Key_A) != m_pressed_keys.end())
    hor_direction -= m_look_dir->getRightDirection();
  if (m_pressed_keys.find(Qt::Key::Key_D) != m_pressed_keys.end())
    hor_direction += m_look_dir->getRightDirection();

  if (m_pressed_keys.find(Qt::Key::Key_Space) != m_pressed_keys.end())
    vert_direction += m_look_dir->getUpDirection();
  if (m_pressed_keys.find(Qt::Key::Key_Shift) != m_pressed_keys.end())
    vert_direction -= m_look_dir->getUpDirection();

  m_position += 0.1 * hor_direction.normalized() + 0.1 * vert_direction;
}

const QVector3D &MotionInputController::getPosition() const {
  return m_position;
}

void MotionInputController::setPosition(const QVector3D &position) {
  m_position = position;
}

} // namespace Kononov

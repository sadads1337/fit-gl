#include "DirectionInputController.hpp"

namespace Kononov {

void DirectionInputController::update(float /*delta*/) {}

void DirectionInputController::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_lastPosition = event->pos();
    m_mousePressed = true;
  }
}

void DirectionInputController::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton && m_mousePressed) {
    handleMove(event->pos());
    m_mousePressed = false;
  }
}

void DirectionInputController::mouseMoveEvent(QMouseEvent *event) {
  if (m_mousePressed) {
    handleMove(event->pos());
  }
}

void DirectionInputController::handleMove(const QPoint &position) {
  auto diff = position - m_lastPosition;
  m_yaw -= static_cast<float>(diff.x()) * m_sensitivity;
  m_pitch -= static_cast<float>(diff.y()) * m_sensitivity;
  m_lastPosition = position;

  if (m_object != nullptr) {
    m_object->setRotation(getRotation());
  }
}

QQuaternion DirectionInputController::getRotation() const noexcept {
  return QQuaternion::fromEulerAngles(m_pitch, m_yaw, 0);
}

QVector3D DirectionInputController::getWalkDirection() const noexcept {
  return QQuaternion::fromEulerAngles(0, m_yaw, 0)
      .rotatedVector(QVector3D(0, 0, -1));
}

QVector3D DirectionInputController::getRightDirection() const noexcept {
  return QQuaternion::fromEulerAngles(0, m_yaw, 0)
      .rotatedVector(QVector3D(1, 0, 0));
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
QVector3D DirectionInputController::getUpDirection() const noexcept {
  return QVector3D(0, 1, 0);
}

const std::shared_ptr<PositionedObject> &
DirectionInputController::getObject() const noexcept {
  return m_object;
}

void DirectionInputController::setObject(
    const std::shared_ptr<PositionedObject> &object) {
  m_object = object;
  if (m_object != nullptr) {
    m_object->setRotation(getRotation());
  }
}

float DirectionInputController::getSensitivity() const noexcept {
  return m_sensitivity;
}

void DirectionInputController::setSensitivity(float sensitivity) {
  DirectionInputController::m_sensitivity = sensitivity;
}

float DirectionInputController::getYaw() const noexcept { return m_yaw; }

void DirectionInputController::setYaw(float yaw) {
  DirectionInputController::m_yaw = yaw;
}

float DirectionInputController::getPitch() const noexcept { return m_pitch; }

void DirectionInputController::setPitch(float pitch) {
  DirectionInputController::m_pitch = pitch;
}

} // namespace Kononov

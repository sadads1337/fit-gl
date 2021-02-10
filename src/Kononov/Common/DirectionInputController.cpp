#include "DirectionInputController.hpp"

namespace Kononov {

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
  if (event->buttons() && m_mousePressed)
    handleMove(event->pos());
}

void DirectionInputController::handleMove(const QPoint &position) {
  auto diff = position - m_lastPosition;
  m_yaw += (float)diff.x() * m_sensitivity;
  m_pitch += (float)diff.y() * m_sensitivity;
  m_lastPosition = position;
}

QQuaternion DirectionInputController::getRotation() const noexcept {
  return QQuaternion::fromEulerAngles(m_pitch, 0, 0) *
         QQuaternion::fromEulerAngles(0, m_yaw, 0);
}

QVector3D DirectionInputController::getWalkDirection() const noexcept {
  return QQuaternion::fromEulerAngles(0, -m_yaw, 0)
      .rotatedVector(QVector3D(0, 0, -1));
}

QVector3D DirectionInputController::getRightDirection() const noexcept {
  return QQuaternion::fromEulerAngles(0, -m_yaw, 0)
      .rotatedVector(QVector3D(1, 0, 0));
}

QVector3D DirectionInputController::getUpDirection() const noexcept {
  return QVector3D(0, 1, 0);
}

float DirectionInputController::getSensitivity() const { return m_sensitivity; }

void DirectionInputController::setSensitivity(float sensitivity) {
  DirectionInputController::m_sensitivity = sensitivity;
}

float DirectionInputController::getYaw() const { return m_yaw; }

void DirectionInputController::setYaw(float yaw) {
  DirectionInputController::m_yaw = yaw;
}

float DirectionInputController::getPitch() const { return m_pitch; }

void DirectionInputController::setPitch(float pitch) {
  DirectionInputController::m_pitch = pitch;
}

} // namespace Kononov

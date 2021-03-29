#include "ConstantRotationController.hpp"

#include <QQuaternion>

namespace Kononov {

void ConstantRotationController::update(float delta) {
  m_angle += m_rotation_speed * delta;
  if (m_object == nullptr) {
    return;
  }
  m_object->setRotation(QQuaternion::fromAxisAndAngle(m_axis, m_angle));
}

const std::shared_ptr<PositionedObject> &
ConstantRotationController::getObject() const {
  return m_object;
}

void ConstantRotationController::setObject(
    const std::shared_ptr<PositionedObject> &object) {
  m_object = object;
}

float ConstantRotationController::getRotationSpeed() const {
  return m_rotation_speed;
}

void ConstantRotationController::setRotationSpeed(float rotation_speed) {
  m_rotation_speed = rotation_speed;
}

const QVector3D &ConstantRotationController::getAxis() const { return m_axis; }

void ConstantRotationController::setRotationAxis(const QVector3D &axis) {
  m_axis = axis;
}

float ConstantRotationController::getAngle() const { return m_angle; }

void ConstantRotationController::setAngle(float angle) { m_angle = angle; }

} // namespace Kononov
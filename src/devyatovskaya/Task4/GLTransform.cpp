#include "GLTransform.h"

void GLTransform::translate(const QVector3D &translation) {
  position_ += translation;
  transform_.translate(position_);
}

void GLTransform::rotate(const float angle, const QVector3D &axis) {
  transform_.rotate(QQuaternion::fromAxisAndAngle(axis, angle));
}

void GLTransform::rotate(const QQuaternion &quaternion) {
  QMatrix4x4 m;
  m.translate(position_);
  m.rotate(quaternion);
  m.translate(-position_);

  transform_ = m * transform_;
}

void GLTransform::reset() {
  position_ = QVector3D(0, 0, 0);
  transform_.setToIdentity();
}

#pragma once
#include <QMatrix4x4>

class GLTransform final {
public:
  QMatrix4x4 transform_;
  QVector3D position_;

  void translate(const QVector3D &translation);
  void rotate(float angle, const QVector3D &axis);
  void rotate(const QQuaternion &quaternion);
  void reset();
};
#pragma once

#include <memory>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>

namespace Kononov {

class PositionedObject {
private:
  std::shared_ptr<PositionedObject> m_parent;

  QVector3D m_position;
  QQuaternion m_rotation;
  QVector3D m_scale;

public:
  [[nodiscard]] QMatrix4x4 getTransformMatrix() const;
  [[nodiscard]] QMatrix4x4 getAbsoluteTransformMatrix() const;
  [[nodiscard]] QVector3D getAbsolutePosition() const;

  [[nodiscard]] const std::shared_ptr<PositionedObject> &getParent() const;
  void setParent(const std::shared_ptr<PositionedObject> &parent);
  [[nodiscard]] const QVector3D &getPosition() const;
  void setPosition(const QVector3D &position);
  [[nodiscard]] const QQuaternion &getRotation() const;
  void setRotation(const QQuaternion &rotation);
  [[nodiscard]] const QVector3D &getScale() const;
  void setScale(const QVector3D &scale);
};

} // namespace Kononov

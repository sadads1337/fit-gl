#pragma once

#include <memory>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>

namespace Kononov {

class PositionedObject {
private:
  std::shared_ptr<PositionedObject> m_parent;

  QVector3D m_position{};
  QQuaternion m_rotation{};
  QVector3D m_scale{1, 1, 1};

public:
  PositionedObject() = default;
  PositionedObject(const PositionedObject &) = default;
  PositionedObject(PositionedObject &&) = default;
  virtual ~PositionedObject() = default;
  PositionedObject &operator=(const PositionedObject &) = default;
  PositionedObject &operator=(PositionedObject &&) = default;

  [[nodiscard]] QMatrix4x4 getTransformMatrix() const noexcept;
  [[nodiscard]] QMatrix4x4 getAbsoluteTransformMatrix() const noexcept;
  [[nodiscard]] QQuaternion getAbsoluteRotation() const noexcept;
  [[nodiscard]] QVector3D getAbsolutePosition() const noexcept;

  [[nodiscard]] QVector3D getForwardDirection() const noexcept;
  [[nodiscard]] QVector3D getRightDirection() const noexcept;
  [[nodiscard]] QVector3D getUpDirection() const noexcept;

  [[nodiscard]] const std::shared_ptr<PositionedObject> &
  getParent() const noexcept;
  void setParent(const std::shared_ptr<PositionedObject> &parent);
  [[nodiscard]] const QVector3D &getPosition() const noexcept;
  void setPosition(const QVector3D &position);
  [[nodiscard]] const QQuaternion &getRotation() const noexcept;
  void setRotation(const QQuaternion &rotation);
  [[nodiscard]] const QVector3D &getScale() const noexcept;
  void setScale(const QVector3D &scale);
};

} // namespace Kononov

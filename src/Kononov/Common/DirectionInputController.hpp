#pragma once

#include <memory>

#include <QMouseEvent>
#include <QQuaternion>
#include <QVector3D>

#include "PositionedObject.hpp"

namespace Kononov {

class DirectionInputController {
public:
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  [[nodiscard]] QQuaternion getRotation() const noexcept;

  [[nodiscard]] QVector3D getWalkDirection() const noexcept;
  [[nodiscard]] QVector3D getRightDirection() const noexcept;
  [[nodiscard]] QVector3D getUpDirection() const noexcept;

  [[nodiscard]] const std::shared_ptr<PositionedObject> &
  getObject() const noexcept;
  void setObject(const std::shared_ptr<PositionedObject> &object);

  [[nodiscard]] float getSensitivity() const noexcept;
  void setSensitivity(float sensitivity);

  [[nodiscard]] float getYaw() const noexcept;
  void setYaw(float yaw);

  [[nodiscard]] float getPitch() const noexcept;
  void setPitch(float pitch);

private:
  void handleMove(const QPoint &position);

  std::shared_ptr<PositionedObject> m_object = nullptr;
  float m_sensitivity = 0;
  bool m_mousePressed = false;
  QPoint m_lastPosition{};
  float m_yaw = 0;
  float m_pitch = 0;
};

} // namespace Kononov

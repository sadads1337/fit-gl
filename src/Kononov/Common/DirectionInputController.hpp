#pragma once

#include <QMouseEvent>
#include <QQuaternion>
#include <QVector3D>

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

  [[nodiscard]] float getSensitivity() const;
  void setSensitivity(float sensitivity);

  [[nodiscard]] float getYaw() const;
  void setYaw(float yaw);

  [[nodiscard]] float getPitch() const;
  void setPitch(float pitch);

private:
  void handleMove(const QPoint &position);

  float m_sensitivity = 0.2;
  bool m_mousePressed = false;
  QPoint m_lastPosition{};
  float m_yaw = 0;
  float m_pitch = 0;
};

} // namespace Kononov

#pragma once

#include <memory>
#include <unordered_set>

#include "DirectionInputController.hpp"
#include <QKeyEvent>
#include <QVector3D>

namespace Kononov {

class MotionInputController {
public:
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void update();

  const std::shared_ptr<PositionedObject> &getObject() const noexcept;
  void setObject(const std::shared_ptr<PositionedObject> &object);
  const std::shared_ptr<DirectionInputController> &
  getDirectionSource() const noexcept;
  void setDirectionSource(
      const std::shared_ptr<DirectionInputController> &direction_source);

  float getMotionSpeed() const noexcept;
  void setMotionSpeed(float motion_speed);

private:
  float m_motion_speed = 0;

  std::shared_ptr<PositionedObject> m_object;
  std::shared_ptr<DirectionInputController> m_direction_source;
  std::unordered_set<int> m_pressed_keys;
};

} // namespace Kononov

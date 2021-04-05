#pragma once

#include <memory>
#include <unordered_set>

#include <QKeyEvent>
#include <QVector3D>

#include "Controller.hpp"
#include "Kononov/Common/Scene/DirectionInputController.hpp"

namespace Kononov {

class MotionInputController : public Controller {
public:
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void update(float delta) override;

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

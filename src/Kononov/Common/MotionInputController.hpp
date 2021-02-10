#pragma once

#include <memory>
#include <unordered_set>

#include "DirectionInputController.hpp"
#include <QKeyEvent>
#include <QVector3D>

namespace Kononov {

class MotionInputController {
public:
  explicit MotionInputController(
      std::shared_ptr<DirectionInputController> look_dir);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void update();

  const QVector3D &getPosition() const;
  void setPosition(const QVector3D &position);

private:
  QVector3D m_position;
  std::shared_ptr<DirectionInputController> m_look_dir;
  std::unordered_set<int> m_pressed_keys;
};

} // namespace Kononov

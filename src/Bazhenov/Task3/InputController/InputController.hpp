#pragma once

#include <unordered_set>
#include <memory>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QQuaternion>
#include <QPoint>
#include <QColorDialog>
#include <QFlags>

namespace Bazhenov {

class InputController {
public:
  [[nodiscard]] QQuaternion getRotation() const noexcept;
  [[nodiscard]] QColor getColor() const noexcept;

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void update();
  [[nodiscard]] bool destructiveCheckNewColorSelected();

private:
  void handleMove(QPoint newPosition);

  Qt::MouseButtons pressedMouseButtons_;
  QPoint mousePosition_;
  const float sensitivity_ = 0.2F;

  QQuaternion rotation_;

  std::unordered_set<Qt::Key> pressedKeys_;

  QColor color_;
  bool newColorSelected_ = false;
};

}

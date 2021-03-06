#ifndef BAZHENOV_TASK1_INPUTCONTROLLER_INPUTCONTROLLER_HPP
#define BAZHENOV_TASK1_INPUTCONTROLLER_INPUTCONTROLLER_HPP

#include <unordered_set>
#include <memory>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QQuaternion>
#include <QPoint>
#include <QColorDialog>

namespace Bazhenov {

class InputController {
public:
  QQuaternion getRotation() const noexcept;
  QColor getColor() const noexcept;

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void update();
  bool destructiveCheckNewColorSelected();

private:
  void handleMove(QPoint newPosition);

  std::unordered_set<Qt::MouseButton> pressedMouseButtons_;
  QPoint mousePosition_;
  const float sensitivity_ = 0.2F;

  QQuaternion rotation_;

  std::unordered_set<Qt::Key> pressedKeys_;

  QColor color_;
  bool newColorSelected_ = false;
};

}

#endif // BAZHENOV_TASK1_INPUTCONTROLLER_INPUTCONTROLLER_HPP

#pragma once

#include <memory>
#include <unordered_set>

#include <QColorDialog>
#include <QFlags>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QQuaternion>

namespace Bazhenov {

class InputController {
public:
  enum class Shader { SHADER_PHONG, SHADER_GOURAUD };

  [[nodiscard]] QQuaternion getRotation() const noexcept;
  [[nodiscard]] QColor getColor() const noexcept;
  [[nodiscard]] Shader getShader() const noexcept;
  [[nodiscard]] bool morphingIsOn() const noexcept;
  [[nodiscard]] bool lightIsOrbiting() const noexcept;

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void update();
  [[nodiscard]] bool destructiveCheckNewColorSelected();

private:
  void handleMove(QPoint newPosition);

  Shader currentShader_ = Shader::SHADER_PHONG;
  bool morphingOn_ = true;
  bool orbitingOn_ = true;

  Qt::MouseButtons pressedMouseButtons_;
  QPoint mousePosition_;
  const float sensitivity_ = 0.2F;

  QQuaternion rotation_;

  std::unordered_set<Qt::Key> pressedKeys_;

  QColor color_;
  bool newColorSelected_ = false;
};

} // namespace Bazhenov

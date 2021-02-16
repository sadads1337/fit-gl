#pragma once

#include "PositionedObject.hpp"

namespace Kononov {

class Viewport {
private:
  float m_x;
  float m_y;
  float m_width;
  float m_height;

public:
  Viewport(float x, float y, float width, float height) noexcept;

  [[nodiscard]] float getX() const noexcept;
  void setX(float x);
  [[nodiscard]] float getY() const noexcept;
  void setY(float y);
  [[nodiscard]] float getWidth() const noexcept;
  void setWidth(float width);
  [[nodiscard]] float getHeight() const noexcept;
  void setHeight(float height);
};

class Camera : public PositionedObject {
private:
  Viewport m_viewport{0, 0, 1, 1};
  QMatrix4x4 m_projection;

public:
  void setPerspective(float fov, float ratio, float near, float far);

  void beginRender(float screen_width, float screen_height);

  [[nodiscard]] QMatrix4x4 getProjectionViewMatrix() const noexcept;

  [[nodiscard]] const Viewport &getViewport() const noexcept;
  void setViewport(const Viewport &viewport);
  [[nodiscard]] const QMatrix4x4 &getProjection() const noexcept;
  void setProjection(const QMatrix4x4 &projection);
};

} // namespace Kononov

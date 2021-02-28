#include "Camera.hpp"

#include <cmath>
#include <stdexcept>

#include "GLUtil.hpp"

namespace Kononov {

Viewport::Viewport(float x, float y, float width, float height) noexcept
    : m_x(x), m_y(y), m_width(width), m_height(height) {}
float Viewport::getX() const noexcept { return m_x; }
void Viewport::setX(float x) { m_x = x; }
float Viewport::getY() const noexcept { return m_y; }
void Viewport::setY(float y) { m_y = y; }
float Viewport::getWidth() const noexcept { return m_width; }
void Viewport::setWidth(float width) { m_width = width; }
float Viewport::getHeight() const noexcept { return m_height; }
void Viewport::setHeight(float height) { m_height = height; }

void Camera::setPerspective(const float in_fov, const float in_ratio, const float in_near, const float in_far) {
  const auto not_valid = !std::isnormal(in_fov) || !std::isnormal(in_ratio) ||
                         !std::isnormal(in_near) || !std::isnormal(in_far);
  if (not_valid) {
    throw std::domain_error("Invalid argument value");
  }
  m_projection.setToIdentity();
  m_projection.perspective(in_fov / in_ratio, in_ratio, in_near, in_far);
}

QMatrix4x4 Camera::getProjectionViewMatrix() const noexcept {
  return m_projection * getAbsoluteTransformMatrix().inverted();
}

void Camera::beginRender(float screen_width, float screen_height) {
  float x = m_viewport.getX() * screen_width;
  float y = m_viewport.getY() * screen_height;
  float w = m_viewport.getWidth() * screen_width;
  float h = m_viewport.getHeight() * screen_height;
  // TODO: cache projection*view matrix
  GL::requireFunctions()->glViewport(x, y, w, h);
}

const Viewport &Camera::getViewport() const noexcept { return m_viewport; }
void Camera::setViewport(const Viewport &viewport) { m_viewport = viewport; }
const QMatrix4x4 &Camera::getProjection() const noexcept {
  return m_projection;
}
void Camera::setProjection(const QMatrix4x4 &projection) {
  m_projection = projection;
}

} // namespace Kononov

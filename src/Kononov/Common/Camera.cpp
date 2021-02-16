#include "Camera.hpp"

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

void Camera::setPerspective(float fov, float ratio, float near, float far) {
  m_projection.setToIdentity();
  m_projection.perspective(fov / ratio, ratio, near, far);
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
  GLUtil::requireFunctions()->glViewport(x, y, w, h);
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
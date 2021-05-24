#include "GLCamera.h"

GLCamera::GLCamera(const QVector3D &pos, float _aspect_ratio)
    : position{pos}, front{0, 0, -1}, right{1, 0, 0}, up{0, 1, 0}, world_up{0,
                                                                            1,
                                                                            0},

      fov{60.f}, yaw{-90.0f}, pitch{0.0f},
      aspect_ratio{_aspect_ratio}, zoom{45.f} {
  update_camera_vectors();
}

QMatrix4x4 GLCamera::get_projection_matrix() const {
  QMatrix4x4 projection;
  projection.perspective(zoom, aspect_ratio, 0.1f, 1000.0f);
  return projection;
}

QMatrix4x4 GLCamera::get_view_matrix() const {
  QMatrix4x4 view;
  view.lookAt(position, position + front, up);
  return view;
}

void GLCamera::update_camera_vectors() {
  QVector3D forward;

  forward.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
  forward.setY(sin(qDegreesToRadians(pitch)));
  forward.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
  front = forward.normalized();

  right = QVector3D::crossProduct(front, world_up).normalized();
  up = QVector3D::crossProduct(right, front).normalized();
}

void GLCamera::translate(const QVector3D &mult) {
  position += front * mult.z();
  position += right * mult.x();
  position += up * mult.y();
  update_camera_vectors();
}
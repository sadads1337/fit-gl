#pragma once
#include <QtMath>
#include <qmatrix4x4.h>
#include <qvector3d.h>

class GLCamera final {
public:
  QVector3D position;
  QVector3D front;
  QVector3D right;
  QVector3D up;
  QVector3D world_up;

  float fov;
  float yaw;
  float pitch;
  float aspect_ratio;
  float zoom;

  explicit GLCamera(const QVector3D &pos, float aspect_ratio = 16.f / 9.f);

  QMatrix4x4 get_projection_matrix() const;
  QMatrix4x4 get_view_matrix() const;

  void update_camera_vectors();
  void translate(const QVector3D &mult);
};
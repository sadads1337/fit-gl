#pragma once

#include <QVector3D>

class Ray {
public:
  Ray(const QVector3D &start_pos, const QVector3D &direction)
      : start_pos(start_pos), direction(direction) {}

  QVector3D get_start_pos() const { return start_pos; }
  QVector3D get_direction() const { return direction; }
  QVector3D at(double t) const { return start_pos + t * direction; }

private:
  QVector3D start_pos;
  QVector3D direction;
};

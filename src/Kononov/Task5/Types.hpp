#pragma once

#include <QVector3D>

namespace Kononov {

struct RayHit {
  QVector3D position;
  QVector3D normal;
  QVector3D color;
  float dist;
  float reflection;
};

struct Ray {
  QVector3D origin;
  QVector3D direction;
};

} // namespace Kononov

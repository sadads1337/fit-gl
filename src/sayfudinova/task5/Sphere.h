#pragma once
#include <QtMath>
#include "Ray.h"
#include "Material.h"

class Sphere {
public:
  QVector3D center;
  float radius;
  Material material;

  Sphere(const QVector3D &c, const float r, Material m);
};

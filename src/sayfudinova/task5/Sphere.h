#pragma once
#include <QtMath>
#include "Interface.h"
#include "Material.h"

class Sphere : public Interface{
public:
  QVector3D center;
  float radius;
  Material material;

  Sphere(const QVector3D &c, const float r, Material m);
  bool ray_intersect(const Ray &ray, float &t0) const override;
};

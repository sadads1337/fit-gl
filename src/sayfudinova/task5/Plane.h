#pragma once
#include "Material.h"
#include "Interface.h"
#include <memory>

class Plane : public Interface{
public:
  QVector3D position;
  QVector3D normal;
  Material material;

  Plane(const QVector3D &p, const QVector3D &n, Material m);
  bool ray_intersect(const Ray &ray, float &t) const override;
};

#pragma once
#include "Material.h"
#include "Ray.h"
#include <QVector3D>
#include <memory>

class Plane {
public:
  Plane(const QVector3D &p, const QVector3D &n, Material m);
  bool ray_intersect(const Ray &ray, float &t) const;

public:
  QVector3D position;
  QVector3D normal;
  Material material;
};

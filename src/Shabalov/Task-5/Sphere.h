#pragma once
#include "Material.h"
#include "Ray.h"
#include <QVector3D>

class Sphere {
public:
  Sphere(const QVector3D &c, float r, Material m);
  bool ray_intersect(const Ray &ray, float &t) const;

public:
  QVector3D center;
  float radius;
  Material material;
};

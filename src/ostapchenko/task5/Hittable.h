#pragma once

#ifndef FIT_GL_HITTABLE_H
#define FIT_GL_HITTABLE_H

#include "Ray.h"
#include <QVector4D>
#include <utility>

struct Material{
  Material() {};
  Material( const float sF, const float  rI, const QVector4D &a) : specularFactor(sF), refractiveIndex(rI), albedo(a){}
  float specularFactor{};
  float refractiveIndex;
  QVector4D albedo;
};

struct hit_record {
  QVector3D p;
  QVector3D normal;
  QVector3D color;
  Material material;
  double t;
  bool front_face;

  inline void set_face_normal(const Ray& r, const QVector3D& outward_normal) {
    front_face = QVector3D::dotProduct(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal :-outward_normal;
  }
};

class Hittable {
public:
  Hittable() = default;
  Hittable(const Hittable &) = default;
  Hittable(Hittable &&) noexcept = default;
  virtual ~Hittable() = default;
  Hittable &operator=(const Hittable &) = default;
  Hittable &operator=(Hittable &&) noexcept = default;

  virtual bool hit(const Ray& r, hit_record& rec) const = 0;
};

#endif // FIT_GL_HITTABLE_H

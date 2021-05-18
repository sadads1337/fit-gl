#ifndef FIT_GL_SPHERE_H
#define FIT_GL_SPHERE_H

#include "Hittable.h"


class Sphere : public Hittable {
public:
  Sphere(QVector3D cen, double r,  Material m, QVector3D c) : center(cen), radius(r), material(m), color(c) {};
  virtual ~Sphere() = default;

  virtual std::optional<HitRecord> hit(const Ray& r) const override;

public:
  QVector3D center;
  double radius;
  Material material;
  QVector3D color;
};


#endif // FIT_GL_SPHERE_H

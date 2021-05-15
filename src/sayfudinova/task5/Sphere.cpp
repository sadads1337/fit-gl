#include "Sphere.h"

Sphere::Sphere(const QVector3D &c, const float r, Material m)
    : center(c), radius(r), material(m) {}

bool Sphere::ray_intersect(const Ray &ray, float &t0) const {
  QVector3D L = center - ray.origin;
  auto tca = QVector3D::dotProduct(L, ray.direction);
  auto d2 = QVector3D::dotProduct(L, L) - tca * tca;
  if (d2 > radius * radius) return false;
  auto thc = sqrtf(radius * radius - d2);
  t0 = tca - thc;
  float t1 = tca + thc;
  if (t0 < 0) t0 = t1;
  if (t0 < 0) return false;
  return true;
}
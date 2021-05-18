#include "Sphere.h"

Sphere::Sphere(const QVector3D &c, const float r, Material m)
    : center(c), radius(r), material(m) {}

bool Sphere::ray_intersect(const Ray &ray, float &t0) const {
  QVector3D to_sphere = center - ray.origin;
  auto dir_projection = QVector3D::dotProduct(to_sphere, ray.direction);
  auto D = QVector3D::dotProduct(to_sphere, to_sphere) - powf(dir_projection, 2);
  if (D > powf(radius, 2)) return false;
  auto sqrt_tmp = sqrtf(powf(radius, 2) - D);
  t0 = dir_projection - sqrt_tmp;
  auto t1 = dir_projection + sqrt_tmp;
  if (t0 < 0) t0 = t1;
  if (t0 < 0) return false;
  return true;
}


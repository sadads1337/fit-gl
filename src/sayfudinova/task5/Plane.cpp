#include "Plane.h"
#include <utility>

Plane::Plane(const QVector3D &p, const QVector3D &n, Material m)
    : position(p), normal(n), material(std::move(m)) {}

bool Plane::ray_intersect(const Ray &ray, float &t) const{
  auto denom = QVector3D::dotProduct(-normal, ray.direction);
  if (std::abs(denom) > 1e-6) {
    QVector3D dist = position - ray.origin;
    t = QVector3D::dotProduct(dist, -normal) / denom;
    return (t >= 0);
  }
  return false;
}

int get_name() {
  return 2;
}

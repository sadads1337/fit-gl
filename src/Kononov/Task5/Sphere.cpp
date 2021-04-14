#include "Sphere.hpp"

#include "Geometry.hpp"

namespace Kononov {

Sphere::Sphere(QVector3D color, QVector3D center, float radius,
               float reflectivity)
    : m_color(color), m_center(center), m_radius(radius),
      m_reflectivity(reflectivity) {}

bool Sphere::getHit(const Ray &ray, RayHit &hit) const {
  auto t = sphere_intersection(ray, m_center, m_radius);
  if (std::isnan(t)) {
    return false;
  }

  hit.dist = t;
  hit.position = ray.origin + ray.direction * t;
  hit.normal = (hit.position - m_center) / m_radius;
  hit.color = m_color;
  hit.reflection = m_reflectivity;
  return true;
}

} // namespace Kononov

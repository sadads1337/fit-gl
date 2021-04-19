#include "Sphere.hpp"

#include "Geometry.hpp"

namespace Kononov {

Sphere::Sphere(QVector3D color, QVector3D center, float radius,
               float reflectivity)
    : m_color(color), m_center(center), m_radius(radius),
      m_reflectivity(reflectivity) {}

std::optional<RayHit> Sphere::getHit(const Ray &ray) const {
  const auto t = sphere_intersection(ray, m_center, m_radius);
  if (!t.has_value()) {
    return std::nullopt;
  }

  RayHit hit;
  hit.dist = t.value();
  hit.position = ray.origin + ray.direction * hit.dist;
  hit.normal = (hit.position - m_center) / m_radius;
  hit.color = m_color;
  hit.reflection = m_reflectivity;
  return hit;
}

} // namespace Kononov

#include "Sphere.hpp"
#include "Bazhenov/Task5/Geometry/Geometry.hpp"

namespace Bazhenov {

Sphere::Sphere(QVector3D color, QVector3D center, float radius,
               float reflectivity)
    : color_(color), center_(center), radius_(radius),
      reflectivity_(reflectivity) {}

std::optional<RayHit> Sphere::getHit(const Ray &ray) const {
  const auto t = sphere_intersection(ray, center_, radius_);
  if (!t.has_value()) {
    return std::nullopt;
  }

  RayHit hit;
  hit.dist = t.value();
  hit.position = ray.origin + ray.direction * hit.dist;
  hit.normal = (hit.position - center_) / radius_;
  hit.color = color_;
  hit.reflection = reflectivity_;
  return hit;
}

} // namespace Bazhenov

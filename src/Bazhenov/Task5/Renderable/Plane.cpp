#include "Plane.hpp"
#include "Bazhenov/Task5/Lighting/Colors.hpp"

namespace Bazhenov {

Plane::Plane(float white_reflectivity, float black_reflectivity)
    : white_reflectivity_(white_reflectivity), black_reflectivity_(black_reflectivity) {}

std::optional<RayHit> Plane::getHit(const Ray &ray) const {
  constexpr auto n = QVector3D(0.0F, 1.0F, 0.0F);
  const auto t = plane_intersection(ray, QVector3D(), n);
  if (!t.has_value()) {
    return std::nullopt;
  }

  RayHit hit;
  hit.dist = t.value();
  hit.position = ray.origin + ray.direction * hit.dist;
  hit.normal = n;
  constexpr auto cell_size = 1.0F;
  const auto c = static_cast<int>(std::floor(hit.position.x() / cell_size)) +
                 static_cast<int>(std::floor(hit.position.z() / cell_size));
  hit.color = c % 2 == 0 ? BLACK : WHITE;
  hit.reflection = c % 2 == 0 ? black_reflectivity_ : white_reflectivity_;
  return hit;
}

}

#include "Ground.hpp"

#include "Colors.hpp"

namespace Kononov {

Ground::Ground(float white_ref, float black_ref)
    : m_white_ref(white_ref), m_black_ref(black_ref) {}

std::optional<RayHit> Ground::getHit(const Ray &ray) const {
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
  hit.reflection = c % 2 == 0 ? m_black_ref : m_white_ref;
  return hit;
}

} // namespace Kononov

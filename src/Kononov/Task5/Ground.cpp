#include "Ground.hpp"

#include "Colors.hpp"

namespace Kononov {

Ground::Ground(float white_ref, float black_ref)
    : m_white_ref(white_ref), m_black_ref(black_ref) {}

bool Ground::getHit(const Ray &ray, RayHit &hit) const {
  const QVector3D n = QVector3D(0.0F, 1.0F, 0.0F);
  auto t = plane_intersection(ray, QVector3D(), n);
  if (std::isnan(t)) {
    return false;
  }

  hit.dist = t;
  hit.position = ray.origin + ray.direction * t;
  hit.normal = n;
  const float cell_size = 1.0F;
  auto c = static_cast<int>(std::floor(hit.position.x() / cell_size)) +
           static_cast<int>(std::floor(hit.position.z() / cell_size));
  hit.color = c % 2 == 0 ? BLACK : WHITE;
  hit.reflection = c % 2 == 0 ? m_black_ref : m_white_ref;
  return true;
}

} // namespace Kononov

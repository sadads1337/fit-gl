#include "Light.hpp"
#include "../Geometry/Geometry.hpp"

namespace Bazhenov {

QVector3D ambient(const float strength, const QVector3D light_color) {
  return strength * light_color;
}

QVector3D diffuse(const QVector3D normal, const QVector3D light_dir,
                  const QVector3D light_color) {
  const auto diff = std::max(dot(normal, light_dir), 0.0F);
  return diff * light_color;
}

QVector3D specular(const QVector3D normal, const QVector3D light_dir,
                   const QVector3D view_dir, const float strength,
                   const float power, const QVector3D light_color) {
  const auto ref_dir = reflect(-light_dir, normal);
  const auto spec = std::pow(std::max(dot(view_dir, ref_dir), 0.0F), power);
  return strength * spec * light_color;
}

} // namespace Bazhenov

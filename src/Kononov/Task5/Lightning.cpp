#include "Lightning.hpp"

#include "Geometry.hpp"

namespace Kononov {

QVector3D ambient(float strength, QVector3D light_color) {
  return strength * light_color;
}

QVector3D diffuse(QVector3D normal, QVector3D light_dir,
                  QVector3D light_color) {
  QVector3D norm = normal;
  float diff = std::max(dot(norm, light_dir), 0.0F);
  return diff * light_color;
}

QVector3D specular(QVector3D normal, QVector3D light_dir, QVector3D view_dir,
                   float strength, float power, QVector3D light_color) {
  QVector3D ref_dir = reflect(-light_dir, normal);
  float spec = std::pow(std::max(dot(view_dir, ref_dir), 0.0F), power);
  return strength * spec * light_color;
}

} // namespace Kononov
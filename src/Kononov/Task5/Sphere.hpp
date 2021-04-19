#pragma once

#include "Renderable.hpp"
#include "Types.hpp"

namespace Kononov {

class Sphere : public Renderable {
private:
  QVector3D m_color;
  QVector3D m_center;
  float m_radius;
  float m_reflectivity;

public:
  Sphere(QVector3D color, QVector3D center, float radius, float reflectivity);

  [[nodiscard]] std::optional<RayHit> getHit(const Ray &ray) const override;
};

} // namespace Kononov

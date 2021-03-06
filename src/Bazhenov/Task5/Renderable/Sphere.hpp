#ifndef FIT_GL_SPHERE_HPP
#define FIT_GL_SPHERE_HPP

#include "../Lighting/Ray.hpp"
#include "Renderable.hpp"

namespace Bazhenov {

class Sphere : public Renderable {
private:
  QVector3D color_;
  QVector3D center_;
  float radius_;
  float reflectivity_;

public:
  Sphere(QVector3D color, QVector3D center, float radius, float reflectivity);

  [[nodiscard]] std::optional<RayHit> getHit(const Ray &ray) const override;
};

} // namespace Bazhenov

#endif // FIT_GL_SPHERE_HPP

#ifndef FIT_GL_PLANE_HPP
#define FIT_GL_PLANE_HPP

#include "../Lighting/Ray.hpp"
#include "Renderable.hpp"

namespace Bazhenov {

class Plane : public Renderable {
private:
  float white_reflectivity_;
  float black_reflectivity_;
  QVector3D position_;
  QVector3D normal_;

public:
  Plane(float white_reflectivity, float black_reflectivity,
        QVector3D position = QVector3D{0.0F, 0.0F, 0.0F},
        QVector3D normal = QVector3D{0.0F, 1.0F, 0.0F});

  [[nodiscard]] std::optional<RayHit> getHit(const Ray &ray) const override;
};

} // namespace Bazhenov

#endif // FIT_GL_PLANE_HPP

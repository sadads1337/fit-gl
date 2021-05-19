#ifndef FIT_GL_PLANE_HPP
#define FIT_GL_PLANE_HPP

#include "Bazhenov/Task5/Lighting/Ray.hpp"
#include "Renderable.hpp"

namespace Bazhenov {

class Plane : public Renderable {
private:
  float white_reflectivity_;
  float black_reflectivity_;

public:
  Plane(float white_reflectivity, float black_reflectivity);

  [[nodiscard]] std::optional<RayHit> getHit(const Ray &ray) const override;
};

}

#endif // FIT_GL_PLANE_HPP

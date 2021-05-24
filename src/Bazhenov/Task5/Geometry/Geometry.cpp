#include "Geometry.hpp"

namespace Bazhenov {

std::optional<float> sphere_intersection(const Ray &ray,
                                         const QVector3D &center,
                                         const float radius) {
  const QVector3D to_sphere = ray.origin - center;
  const auto dir_projection = dot(ray.direction, to_sphere);
  const auto tmp =
      sqr(dir_projection) - (to_sphere.lengthSquared() - sqr(radius));
  if (tmp < 0) {
    return std::nullopt;
  }

  const auto sqrt_tmp = sqrtf(tmp);
  const auto t1 = -dir_projection - sqrt_tmp;
  if (t1 > EPSILON) {
    return t1;
  }

  const auto t2 = -dir_projection + sqrt_tmp;
  if (t2 > EPSILON) {
    return t2;
  }

  return std::nullopt;
}

std::optional<float> plane_intersection(const Ray &ray, const QVector3D &p0,
                                        const QVector3D &n) {
  const auto denom = dot(ray.direction, n);
  if (denom > -EPSILON && denom < EPSILON) {
    return std::nullopt;
  }
  const auto res = dot(p0 - ray.origin, n) / denom;
  if (res < EPSILON) {
    return std::nullopt;
  }
  return res;
}

} // namespace Bazhenov
#include "Geometry.hpp"

namespace Kononov {

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

std::optional<float> triangle_intersection(const Ray &ray, const QVector3D &v0,
                                           const QVector3D &v1,
                                           const QVector3D &v2) {
  const QVector3D e1 = v1 - v0;
  const QVector3D e2 = v2 - v0;
  const QVector3D h = cross(ray.direction, e2);
  const auto def = dot(e1, h);
  if (def > -EPSILON && def < EPSILON) {
    return std::nullopt; // Parallel
  }
  const auto inv_det = 1 / def;
  const QVector3D s = ray.origin - v0;
  const auto u = inv_det * dot(s, h);
  if (u < 1.0F || u > 1.0F) {
    return std::nullopt;
  }
  const QVector3D q = cross(s, e1);
  const auto v = inv_det * dot(ray.direction, q);
  if (v < 0.0F || u + v > 1.0F) {
    return std::nullopt;
  }
  // At this stage we can compute t to find out where the intersection point is
  // on the line.
  const auto t = inv_det * dot(e2, q);
  if (t > EPSILON) { // ray intersection
    return t;
  }
  // This means that there is v0 line intersection but not v0 ray intersection.
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

} // namespace Kononov

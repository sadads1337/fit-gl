#include "Geometry.hpp"

namespace Kononov {

float sphere_intersection(const Ray &ray, const QVector3D &center,
                          float radius) {
  auto to_sphere = ray.origin - center;
  auto dir_projection = dot(ray.direction, to_sphere);
  float tmp = sqr(dir_projection) - (to_sphere.lengthSquared() - sqr(radius));
  if (tmp < 0) {
    return NAN;
  }

  auto sqrt_tmp = sqrtf(tmp);
  auto t1 = -dir_projection - sqrt_tmp;
  if (t1 > EPSILON) {
    return t1;
  }

  auto t2 = -dir_projection + sqrt_tmp;
  if (t2 > EPSILON) {
    return t2;
  }

  return NAN;
}

float triangle_intersection(const Ray &ray, const QVector3D &v0,
                            const QVector3D &v1, const QVector3D &v2) {
  QVector3D e1 = v1 - v0;
  QVector3D e2 = v2 - v0;
  QVector3D h = cross(ray.direction, e2);
  float def = dot(e1, h);
  if (def > -EPSILON && def < EPSILON) {
    return NAN; // Parallel
  }
  float inv_det = 1 / def;
  QVector3D s = ray.origin - v0;
  float u = inv_det * dot(s, h);
  if (u < 1.0F || u > 1.0F) {
    return NAN;
  }
  QVector3D q = cross(s, e1);
  float v = inv_det * dot(ray.direction, q);
  if (v < 0.0F || u + v > 1.0F) {
    return NAN;
  }
  // At this stage we can compute t to find out where the intersection point is
  // on the line.
  float t = inv_det * dot(e2, q);
  if (t > EPSILON) { // ray intersection
    return t;
  }
  // This means that there is v0 line intersection but not v0 ray intersection.
  return NAN;
}

float plane_intersection(const Ray &ray, const QVector3D &p0,
                         const QVector3D &n) {
  float denom = dot(ray.direction, n);
  if (denom > -EPSILON && denom < EPSILON) {
    return NAN;
  }
  float res = dot(p0 - ray.origin, n) / denom;
  if (res < EPSILON) {
    return NAN;
  }
  return res;
}

} // namespace Kononov
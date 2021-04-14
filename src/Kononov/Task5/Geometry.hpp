#pragma once

#include <cmath>

#include "Types.hpp"

namespace Kononov {

constexpr float EPSILON = 1e-3F;

inline float dot(const QVector3D &a, const QVector3D &b) {
  return QVector3D::dotProduct(a, b);
}
inline QVector3D cross(const QVector3D &a, const QVector3D &b) {
  return QVector3D::crossProduct(a, b);
}
inline QVector3D reflect(const QVector3D &d, const QVector3D &n) {
  return d - 2 * dot(d, n) * n;
}
inline float sqr(float a) { return a * a; }

float sphere_intersection(const Ray &ray, const QVector3D &center,
                          float radius);

float triangle_intersection(const Ray &ray, const QVector3D &v0,
                            const QVector3D &v1, const QVector3D &v2);

float plane_intersection(const Ray &ray, const QVector3D &p0,
                         const QVector3D &n);
} // namespace Kononov
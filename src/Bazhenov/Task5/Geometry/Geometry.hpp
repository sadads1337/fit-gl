#ifndef FIT_GL_GEOMETRY_HPP
#define FIT_GL_GEOMETRY_HPP

#include <cmath>
#include <optional>

#include "../Lighting/Ray.hpp"

namespace Bazhenov {

constexpr float EPSILON = 1e-3F;

// There are a lot of geometric calculations in the code. Therefore, I believe
// that the call to the vector product functions should be short.
inline constexpr auto dot = &QVector3D::dotProduct;
inline constexpr auto cross = &QVector3D::crossProduct;
inline QVector3D reflect(const QVector3D &d, const QVector3D &n) {
  return d - 2 * dot(d, n) * n;
}
inline float sqr(float a) { return a * a; }

std::optional<float> sphere_intersection(const Ray &ray,
                                         const QVector3D &center, float radius);

std::optional<float> plane_intersection(const Ray &ray, const QVector3D &p0,
                                        const QVector3D &n);

} // namespace Bazhenov

#endif // FIT_GL_GEOMETRY_HPP

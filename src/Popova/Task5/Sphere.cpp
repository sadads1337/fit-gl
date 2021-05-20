
#include "Sphere.hpp"
#include <cmath>

bool Sphere::intersect(const Ray &ray, float &p) const {
  QVector3D dist = ray.origin - center;
  const auto product = QVector3D::dotProduct(ray.direction, dist);
  const auto squared_length = ray.direction.lengthSquared();
  const auto dist_squared = dist.lengthSquared() - pow(radius, 2);

  const auto deskriminant = pow(product, 2) - squared_length * dist_squared;
  // Ray passes mime sphere
  if (deskriminant < 0)
    return false;
  const auto sqrt_deskriminant = sqrt(deskriminant);
  auto root1 = (-product - sqrt_deskriminant) / squared_length;
  auto root2 = (-product + sqrt_deskriminant) / squared_length;

  if (root1 < 0.0) {
    root1 = root2;
    if (root1 < 0.0)
      return false;
  }
  p = root1;
  return true;
}
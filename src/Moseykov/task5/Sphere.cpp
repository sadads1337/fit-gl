#include "Sphere.h"
#include "QtMath"

std::optional<HitRecord> Sphere::hit(const Ray &r) const {
  HitRecord hit;
  QVector3D oc = r.origin() - center;
  const auto a = r.direction().lengthSquared();
  const auto b_hf = QVector3D::dotProduct(oc, r.direction());
  const auto c = oc.lengthSquared() - radius * radius;
  const auto discriminant = b_hf * b_hf - a * c;
  if (discriminant < 0) {
    return std::nullopt;
  }
  const auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-b_hf - sqrtd) / a;
  if (root < 0 || INFINITY < root) {
    root = (-b_hf + sqrtd) / a;
    if (root < 0 || INFINITY < root) {
      return std::nullopt;
    }
  }
  hit.t = root;
  hit.p = r.at(hit.t);
  QVector3D outward_normal = (hit.p - center) / radius;
  hit.face_norm(r, outward_normal);
  hit.material = material;
  hit.color = color;
  return hit;
}

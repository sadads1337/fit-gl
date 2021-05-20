#include "Sphere.h"
#include "QtMath"

std::optional<HitRecord> Sphere::hit(const Ray &r) const {
  HitRecord rec;
  QVector3D oc = r.origin() - center;
  const auto a = r.direction().lengthSquared();
  const auto half_b = QVector3D::dotProduct(oc, r.direction());
  const auto c = oc.lengthSquared() - radius * radius;

  const auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return std::nullopt;
  const auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < 0 || INFINITY < root) {
    root = (-half_b + sqrtd) / a;
    if (root < 0 || INFINITY < root)
      return std::nullopt;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  QVector3D outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.material = material;
  rec.color = color;

  return rec;
}

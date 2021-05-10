#include "Sphere.h"
#include "QtMath"

bool Sphere::hit(const Ray& r, hit_record& rec) const {
  QVector3D oc = r.origin() - center;
  auto a = r.direction().lengthSquared();
  auto half_b = QVector3D::dotProduct(oc, r.direction());
  auto c = oc.lengthSquared() - radius*radius;

  auto discriminant = half_b*half_b - a*c;
  if(discriminant < 0) return false;
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < 0 || INFINITY < root) {
    root = (-half_b + sqrtd) / a;
    if(root < 0 || INFINITY < root)
      return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  QVector3D outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.material = material;
  rec.color = color;

  return true;
}

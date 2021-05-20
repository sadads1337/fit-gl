#ifndef FIT_GL_HITTABLE_H
#define FIT_GL_HITTABLE_H

#include "Ray.h"
#include <QVector4D>
#include <optional>
#include <utility>

struct Material {
  float specularFactor;
  float refractiveIndex;
  QVector4D albedo;
};

struct HitRecord {
  QVector3D p;
  QVector3D normal;
  QVector3D color;
  Material material;
  double t;
  bool front_face;

  inline void set_face_normal(const Ray &r, const QVector3D &outward_normal) {
    front_face = QVector3D::dotProduct(r.direction(), outward_normal) < 0.;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  Hittable() = default;
  virtual ~Hittable() = default;

  virtual std::optional<HitRecord> hit(const Ray &r) const = 0;
};

#endif // FIT_GL_HITTABLE_H

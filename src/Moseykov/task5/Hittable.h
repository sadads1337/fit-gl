#ifndef FIT_GL_HITTABLE_H
#define FIT_GL_HITTABLE_H

#include "Ray.h"
#include <QVector4D>
#include <utility>
#include <optional>


struct Material{
  float specularFactor;
  float refractiveIndex;
  QVector4D albedo;
};

struct HitRecord {
    Material material;
    QVector3D p;
    QVector3D norm;
    QVector3D color;
    double t;
    bool front;
    inline void face_norm(const Ray& r, const QVector3D& outward_norm) {
        front = QVector3D::dotProduct(r.direction(), outward_norm) < 0.;
        norm = front ? outward_norm :-outward_norm;
  }
};

class Hittable {

public:
  Hittable() = default;
  virtual ~Hittable() = default;
  [[nodiscard]] virtual std::optional<HitRecord> hit(const Ray& r) const = 0;
};

#endif // FIT_GL_HITTABLE_H

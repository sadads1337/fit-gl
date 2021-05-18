#ifndef FIT_GL_PLANE_H
#define FIT_GL_PLANE_H
#include "Hittable.h"
#include "QImage"

class Plane : public Hittable {
public:
  Plane(QVector3D p, QVector3D n) : position(p), normal(n) {};
  virtual ~Plane() = default;

  virtual std::optional<HitRecord> hit(const Ray& r) const override;

public:
  QVector3D position;
  QVector3D normal;

};


#endif // FIT_GL_PLANE_H

#ifndef FIT_GL_FLOOR_H
#define FIT_GL_FLOOR_H
#include "Hittable.h"
#include "QImage"

class Floor : public Hittable {

public:
  Floor(QVector3D p, QVector3D n) : pos(p), norm(n) {};
  ~Floor() override = default;
  [[nodiscard]] std::optional<HitRecord> hit(const Ray& r) const override;

private:
  QVector3D pos;
  QVector3D norm;
};


#endif // FIT_GL_FLOOR_H

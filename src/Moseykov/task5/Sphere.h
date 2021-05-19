#ifndef FIT_GL_SPHERE_H
#define FIT_GL_SPHERE_H

#include "Hittable.h"


class Sphere : public Hittable {

public:
    Sphere(QVector3D center, double r,  Material m, QVector3D c) : center(center), radius(r), material(m), color(c) {};
    ~Sphere() override = default;
    [[nodiscard]] std::optional<HitRecord> hit(const Ray& r) const override;

private:
    QVector3D center;
    double radius;
    Material material;
    QVector3D color;

};


#endif // FIT_GL_SPHERE_H

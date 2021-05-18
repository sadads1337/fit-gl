#pragma once

#include "Hittable.h"

class Sphere : public Hittable {
public:
    Sphere(QVector3D cen, double r, Material m, QVector3D c)
        : center(cen), radius(r), material(m), color(c) {};
    virtual ~Sphere() = default;
    virtual std::optional<Hit> intersect(const Ray& ray) const override;

private:
    QVector3D center;
    double radius;
    Material material;
    QVector3D color;
};


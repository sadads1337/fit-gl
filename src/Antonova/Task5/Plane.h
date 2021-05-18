#pragma once

#include "Hittable.h"

class Plane : public Hittable {
public:
    Plane(QVector3D p, QVector3D n) : position(p), normal(n) {};
    virtual ~Plane() = default;
    virtual std::optional<Hit> intersect(const Ray& ray) const override;

public:
    QVector3D position;
    QVector3D normal;
};

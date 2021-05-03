#pragma once
#include <QVector3D>
#include "Ray.h"
#include "Material.h"

class Sphere {
public:
    Sphere(const QVector3D &c, float r, Material m);
    bool ray_intersect(const Ray &ray, float &t) const;
public:
    QVector3D center;
    float radius;
    Material material;
};


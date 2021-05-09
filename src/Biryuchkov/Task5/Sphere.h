#ifndef BIRYUCHKOV_SPHERE_H
#define BIRYUCHKOV_SPHERE_H

#pragma once
#include <QVector3D>
#include "Hit_ray.h"
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
#endif //BIRYUCHKOV_SPHERE_H

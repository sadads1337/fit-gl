#ifndef BIRYUCHKOV_SURFACE_H
#define BIRYUCHKOV_SURFACE_H

#pragma once
#include <QVector3D>
#include "Hit_ray.h"
#include "Material.h"
#include <memory>

class Surface {
public:
    Surface(const QVector3D &p,const QVector3D &n, Material m);
    bool ray_intersect(const Ray &ray, float &t) const;
public:
    QVector3D position;
    QVector3D normal;
    Material material;
};
#endif //BIRYUCHKOV_SURFACE_H

#pragma once

#include <QVector4D>
#include "Ray.h"

struct Material{
    float specularFactor;
    float refractiveIndex;
    QVector4D light_params;
};

struct Hit{
public:
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    Material material;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const QVector3D& outward_normal) {
        front_face = QVector3D::dotProduct(r.get_direction(), outward_normal) < 0.;
        normal = front_face ? outward_normal :-outward_normal;
    }
};


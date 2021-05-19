#include "Plane.h"
#include <utility>

constexpr auto precision = 1e-6;

Plane::Plane(const QVector3D &p, const QVector3D &n, Material m) : position(p), normal(n), material(std::move(m)){
}

bool Plane::ray_intersect(const Ray &ray, float &distance) const {
    const auto denom = QVector3D::dotProduct(-normal, ray.direction);
    if(std::abs(denom) > precision){
        QVector3D dist = position - ray.origin;
        distance = QVector3D::dotProduct(dist, -normal) / denom;
        return (distance >= 0.f);
    }
    return false;
}

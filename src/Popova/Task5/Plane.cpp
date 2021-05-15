#include "Plane.hpp"
#include <cmath>
Plane::Plane(const QVector3D &p, const QVector3D &norm, Material m) : position(p), normal(norm), material(std::move(m)){
}

bool Plane::intersect(const Ray &ray, float &p) const {
    auto c = QVector3D::dotProduct(ray.direction, normal);
    if(std::abs(c) > 1e-6){
        QVector3D dist = position - ray.origin;
        p = QVector3D::dotProduct(normal, dist) / c;
        return (p >= 0);
}
    return false;
}
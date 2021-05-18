#include "Plane.hpp"
#include <cmath>

bool Plane::intersect(const Ray &ray, float &distance) const {
    const auto product = QVector3D::dotProduct(ray.direction, normal);
    constexpr auto precision = 1e-6;
    if(std::abs(product) > precision){
        QVector3D dist = position - ray.origin;
        distance = QVector3D::dotProduct(normal, dist) / product;
        return (distance >= 0);
}
    return false;
}
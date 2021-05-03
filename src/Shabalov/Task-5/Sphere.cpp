#include "Sphere.h"
#include <utility>

Sphere::Sphere(const QVector3D &c,const float r, Material m)
: center(c), radius(r), material(std::move(m)){}

bool Sphere::ray_intersect(const Ray &ray, float &t) const {
    QVector3D L =  center - ray.origin;
    auto tca = QVector3D::dotProduct(L,ray.direction);
    auto d2 = QVector3D::dotProduct(L,L) - tca*tca;
    if(d2 > radius * radius) return false;
    auto thc = std::sqrt(radius * radius - d2);
    auto t0 = tca - thc;
    auto t1 = tca + thc;

    if(t0 < 0.0){
        t0 = t1;
        if(t0 < 0.0) return false;
    }
    t = t0;
    return true;
}

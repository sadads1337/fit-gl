
#include <cmath>
#include "Sphere.hpp"

Sphere::Sphere(const QVector3D &center, const float r, Material m)
: center(center), radius(r), material(std::move(m)){}

bool Sphere::intersect(const Ray &ray, float &p) const {
    QVector3D dist =  ray.origin - center;
    auto b = QVector3D::dotProduct(ray.direction, dist);
    auto a = ray.direction.lengthSquared();
    auto c = dist.lengthSquared() - pow(radius, 2);

    auto deskriminant = pow(b,2) - a*c;
    //Ray passes mime sphere
    if(deskriminant < 0) 
        return false;
    auto sqrt_deskriminant = sqrt(deskriminant);
    auto root1 = (-b - sqrt_deskriminant)/a;
    auto root2 = (-b + sqrt_deskriminant)/a;

    if(root1 < 0.0){
        root1 = root2;
        if(root1 < 0.0) 
            return false;
    }
    p = root1;
    return true;

}
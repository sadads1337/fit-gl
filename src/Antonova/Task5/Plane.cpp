#include "Plane.h"
#include "cmath"

constexpr auto precision = 1e-6;

std::optional<Hit> Plane::intersect(const Ray& ray) const{

    const auto dir_y = QVector3D::dotProduct(ray.get_direction(), normal);

    if(std::abs(dir_y) <= precision) return std::nullopt;

    const QVector3D dist = position - ray.get_start_pos();
    const auto t = QVector3D::dotProduct(dist, normal) / dir_y;

    if(t < precision) return std::nullopt;

    Hit occurred_hit;
    occurred_hit.t = t;
    occurred_hit.normal = normal;
    occurred_hit.position = ray.at(t);

    constexpr auto cell_size = 0.4F;
    const auto c = static_cast<int>(std::floor(occurred_hit.position.x() / cell_size)) +
                   static_cast<int>(std::floor(occurred_hit.position.z() / cell_size));
    if(c % 2 == 0){
        occurred_hit.color = QVector3D(1.0f, 1.0f, 1.0f);
        occurred_hit.material.light_params = QVector4D(0.6f, 0.3f, 0.1f, 0.0f);
        occurred_hit.material.specularFactor = 50;
        occurred_hit.material.refractiveIndex = 1;
    }
    else{
        occurred_hit.color = QVector3D(166.0f/255, 54.0f/255, 153.0f/255);
        occurred_hit.material.light_params = QVector4D(0.6f, 0.3f, 0.1f, 0.0f);
        occurred_hit.material.specularFactor = 50;
        occurred_hit.material.refractiveIndex = 1;
    }

    return occurred_hit;


}
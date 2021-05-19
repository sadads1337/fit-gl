#include "Floor.h"
#include "cmath"

constexpr auto precision = 1e-6;

std::optional<HitRecord> Floor::hit(const Ray& r) const{
    const auto dir_y = QVector3D::dotProduct(r.direction(), norm);
    if(std::abs(dir_y) <= precision) { return std::nullopt; }
    const QVector3D dist = pos - r.origin();
    const auto t = QVector3D::dotProduct(dist, norm) / dir_y;
    if(t < precision) { return std::nullopt; }
    HitRecord hit;
    hit.t = t;
    hit.norm = norm;
    hit.p = r.at(t);
    constexpr auto cell_size = 0.4F;
    const auto c = static_cast<int>(std::floor(hit.p.x() / cell_size)) +
                       static_cast<int>(std::floor(hit.p.z() / cell_size));
    if(c % 2 == 0){
         hit.color = QVector3D(1.0f, 1.0f, 1.0f);
         hit.material.albedo = QVector4D(0.6f, 0.3f, 0.1f, 0.0f);
         hit.material.specularFactor = 50;
         hit.material.refractiveIndex = 1;
        }
    else{
         hit.color = QVector3D(0.0f, 0.9f, 0.1f);
         hit.material.albedo = QVector4D(0.6f, 0.3f, 0.1f, 0.0f);
         hit.material.specularFactor = 50;
         hit.material.refractiveIndex = 1;
        }

    return hit;


}
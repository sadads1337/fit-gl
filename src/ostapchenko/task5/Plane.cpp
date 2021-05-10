#include "Plane.h"
#include "cmath"

bool Plane::hit(const Ray& r, hit_record& rec) const{
    auto dir_y = QVector3D::dotProduct(r.direction(), normal);
    if(std::abs(dir_y) > 1e-6){
      QVector3D dist = position - r.origin();
      auto t = QVector3D::dotProduct(dist, normal) / dir_y;
      if(t >= 1e-6) {
        rec.t = t;
        rec.normal = normal;
        rec.p = r.at(t);

        constexpr auto cell_size = 0.4F;
        const auto c = static_cast<int>(std::floor(rec.p.x() / cell_size)) +
                       static_cast<int>(std::floor(rec.p.z() / cell_size));
        if(c % 2 == 0){
          rec.color = QVector3D(1.0f, 1.0f, 1.0f);
          rec.material.albedo = QVector4D(0.6f, 0.3f, 0.1f, 0.0f);
          rec.material.specularFactor = 50;
          rec.material.refractiveIndex = 1;

        }
        else{
          rec.color = QVector3D(1.0f, 0.0f, 0.0f);
          rec.material.albedo = QVector4D(0.6f, 0.3f, 0.1f, 0.0f);
          rec.material.specularFactor = 50;
          rec.material.refractiveIndex = 1;
        }

        return true;
      }
      return false;
    }
    return false;

}
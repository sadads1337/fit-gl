#include "Sphere.h"
#include "QtMath"

std::optional<Hit> Sphere::intersect(const Ray& ray) const {
    Hit occurred_hit;
    QVector3D oc = ray.get_start_pos() - center;
    const auto a = ray.get_direction().lengthSquared();
    const auto half_b = QVector3D::dotProduct(oc, ray.get_direction());
    const auto c = oc.lengthSquared() - radius*radius;

    const auto discriminant = half_b*half_b - a*c;
    if(discriminant < 0) return std::nullopt;
    const auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < 0 || INFINITY < root) {
        root = (-half_b + sqrtd) / a;
        if(root < 0 || INFINITY < root)
            return std::nullopt;
    }

    occurred_hit.t = root;
    occurred_hit.position = ray.at(occurred_hit.t);
    QVector3D outward_normal = (occurred_hit.position - center) / radius;
    occurred_hit.set_face_normal(ray, outward_normal);
    occurred_hit.material = material;
    occurred_hit.color = color;

    return occurred_hit;
}
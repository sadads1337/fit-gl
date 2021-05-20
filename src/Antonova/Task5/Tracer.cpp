#include "Tracer.h"
#include "QtMath"

QVector3D Tracer::mix(const QVector3D &a, const QVector3D &b, const float k) {
  return a * k + b * (1 - k);
}

QVector3D Tracer::reflect(const QVector3D &d, const QVector3D &n) {
  return d - 2.f * n * QVector3D::dotProduct(d, n);
}

QVector3D Tracer::refract(const QVector3D &incident, const QVector3D &normal,
                          const float n_1, const float n_2 = 1.f) {
  auto cos_1 =
      -std::max(-1.f, std::min(1.f, QVector3D::dotProduct(incident, normal)));
  if (cos_1 < 0.f)
    return refract(incident, -normal, n_2, n_1);
  auto ratio = n_2 / n_1;
  auto cos_2 = sqrtf(1 - ratio * ratio * (1 - cos_1 * cos_1));
  return ratio * incident + (ratio * cos_1 - cos_2) * normal;
}

QVector3D Tracer::trace(const Ray &ray,
                        const std::vector<std::shared_ptr<Hittable>> &objects,
                        int reflection_depth, LightConditions cond) {

  if (reflection_depth == 0)
    return cond.background_color;

  QVector3D ambient_coeff = cond.ambient_color * cond.ambient_strength;

  for (const auto &o : objects) {
    float diffuse_light_intensity = 0.0F;
    float specular_light_intensity = 0.0F;
    const auto occurred_hit = o->intersect(ray);
    if (occurred_hit.has_value()) {
      QVector3D light_dir =
          (cond.light_pos - occurred_hit->position).normalized();
      float light_distance = (cond.light_pos - occurred_hit->position).length();
      QVector3D reflect_dir =
          reflect(ray.get_direction(), occurred_hit->position).normalized();
      QVector3D refract_dir = refract(ray.get_direction(), occurred_hit->normal,
                                      occurred_hit->material.refractiveIndex)
                                  .normalized();
      QVector3D reflect_orig =
          QVector3D::dotProduct(reflect_dir, occurred_hit->normal) < 0
              ? occurred_hit->position - occurred_hit->normal * 1e-3f
              : occurred_hit->position + occurred_hit->normal * 1e-3f;
      QVector3D refract_orig =
          QVector3D::dotProduct(refract_dir, occurred_hit->normal) < 0
              ? occurred_hit->position - occurred_hit->normal * 1e-3f
              : occurred_hit->position + occurred_hit->normal * 1e-3f;
      QVector3D reflect_color = trace(Ray(reflect_orig, reflect_dir), objects,
                                      reflection_depth - 1, cond);
      QVector3D refract_color = trace(Ray(refract_orig, refract_dir), objects,
                                      reflection_depth - 1, cond);

      QVector3D shadow_orig =
          QVector3D::dotProduct(light_dir, occurred_hit->normal) < 0
              ? occurred_hit->position - occurred_hit->normal * 1e-3f
              : occurred_hit->position + occurred_hit->normal * 1e-3f;
      const auto shadow_rec = o->intersect(Ray(shadow_orig, light_dir));
      if (!(shadow_rec.has_value()) || shadow_rec->t > light_distance) {
        diffuse_light_intensity = std::max(
            0.f, QVector3D::dotProduct(light_dir, occurred_hit->normal));
        specular_light_intensity =
            std::pow(std::max(0.f, QVector3D::dotProduct(
                                       reflect(light_dir, occurred_hit->normal),
                                       ray.get_direction())),
                     occurred_hit->material.specularFactor) *
            cond.light_intensity;
      }
      auto k = std::exp(
          -(occurred_hit->position - ray.get_start_pos()).length() / 100.f);
      auto resultColor = ambient_coeff * occurred_hit->color +
                         occurred_hit->color * diffuse_light_intensity *
                             occurred_hit->material.light_params.x() +
                         cond.light_color * specular_light_intensity *
                             occurred_hit->color *
                             occurred_hit->material.light_params.y() +
                         reflect_color * occurred_hit->color *
                             occurred_hit->material.light_params.z() +
                         refract_color * occurred_hit->color *
                             occurred_hit->material.light_params.w();
      return mix(resultColor, cond.background_color, k);
    }
  }
  return cond.background_color;
}
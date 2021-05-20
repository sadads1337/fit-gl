#pragma once

#include "Hit.h"
#include "Hittable.h"
#include "Ray.h"
#include <memory>

struct LightConditions {
  QVector3D background_color;

  float ambient_strength;
  QVector3D ambient_color;
  QVector3D light_pos;
  QVector3D light_color;
  float light_intensity;
};

class Tracer {
public:
  Tracer(){};
  ~Tracer(){};

  QVector3D reflect(const QVector3D &d, const QVector3D &n);
  QVector3D refract(const QVector3D &incident, const QVector3D &normal,
                    const float n_1, const float n_2);
  QVector3D trace(const Ray &ray,
                  const std::vector<std::shared_ptr<Hittable>> &objects,
                  int reflection_depth, LightConditions cond);
  QVector3D mix(const QVector3D &a, const QVector3D &b, const float k);
};

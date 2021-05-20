#pragma once

#include "Hit.h"
#include "Ray.h"
#include <QVector4D>
#include <optional>
#include <utility>

class Hittable {
public:
  Hittable() = default;
  virtual ~Hittable() = default;
  virtual std::optional<Hit> intersect(const Ray &ray) const = 0;
};

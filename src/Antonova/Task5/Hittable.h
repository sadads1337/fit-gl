#pragma once

#include "Ray.h"
#include "Hit.h"
#include <utility>
#include <optional>
#include <QVector4D>

class Hittable {
public:
    Hittable() = default;
    virtual ~Hittable() = default;
    virtual std::optional<Hit> intersect(const Ray& ray) const = 0;
};

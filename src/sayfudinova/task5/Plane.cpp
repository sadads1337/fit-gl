#include "Plane.h"
#include <utility>

Plane::Plane(const QVector3D &p, const QVector3D &n, Material m)
    : position(p), normal(n), material(std::move(m)) {}

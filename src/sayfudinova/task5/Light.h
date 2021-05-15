#pragma once
#include <QVector3D>

struct Light {
  QVector3D position;
  float intensity;

  Light(const QVector3D &p, const float &i) : position(p), intensity(i) {}
};
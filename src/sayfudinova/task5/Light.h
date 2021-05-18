#pragma once
#include <QVector3D>

struct Light {
  QVector3D position = {20.f, 30.f, -25.f};
  float intensity = 1.5f;
};
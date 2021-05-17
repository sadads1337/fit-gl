#pragma once
#include <QVector3D>

struct Ray {
  QVector3D origin;
  QVector3D direction;

  Ray(const QVector3D o, const QVector3D d) : origin(o), direction(d) {}
};

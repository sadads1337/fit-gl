#pragma once
#include <QVector3D>

#ifndef FIT_GL_RAY_H
#define FIT_GL_RAY_H
class Ray {
public:
  Ray() {}
  Ray(const QVector3D& origin, const QVector3D& direction)
      : orig(origin), dir(direction)
  {}

  [[nodiscard]] QVector3D origin() const  { return orig; }
  [[nodiscard]] QVector3D direction() const { return dir; }

  [[nodiscard]] QVector3D at(double t) const {
    return orig + t*dir;
  }

public:
  QVector3D orig;
  QVector3D dir;
};
#endif // FIT_GL_RAY_H

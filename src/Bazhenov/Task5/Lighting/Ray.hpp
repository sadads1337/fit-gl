#ifndef FIT_GL_RAY_HPP
#define FIT_GL_RAY_HPP

#include <QVector3D>

namespace Bazhenov {

struct RayHit {
  QVector3D position;
  QVector3D normal;
  QVector3D color;
  float dist;
  float reflection;
};

struct Ray {
  QVector3D origin;
  QVector3D direction;
};

} // namespace Bazhenov

#endif // FIT_GL_RAY_HPP

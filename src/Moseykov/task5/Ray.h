#ifndef FIT_GL_RAY_H
#define FIT_GL_RAY_H
#include <QVector3D>

class Ray {
    
public:
  Ray(const QVector3D& origin, const QVector3D& direction) : orig(origin), direct(direction)  {}
  [[nodiscard]] QVector3D origin() const  { return orig; }
  [[nodiscard]] QVector3D direction() const { return direct; }
  [[nodiscard]] QVector3D at(double t) const {
    return orig + t * direct;
  }

private:
  QVector3D orig;
  QVector3D direct;
};
#endif // FIT_GL_RAY_H

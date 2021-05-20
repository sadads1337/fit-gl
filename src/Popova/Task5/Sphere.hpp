
#include "Material.hpp"
#include "Types.hpp"
#include <QVector3D>

class Sphere {
public:
  bool intersect(const Ray &ray, float &t) const;

public:
  QVector3D center;
  float radius;
  Material material;
};
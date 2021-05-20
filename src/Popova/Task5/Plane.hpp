
#include "Material.hpp"
#include "Types.hpp"
#include <QVector3D>

class Plane {
public:
  bool intersect(const Ray &ray, float &t) const;

public:
  QVector3D position;
  QVector3D normal;
  Material material;
};
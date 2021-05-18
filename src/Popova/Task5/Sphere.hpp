
#include <QVector3D>
#include "Types.hpp"
#include "Material.hpp"

class Sphere {
public:
    bool intersect(const Ray &ray, float &t) const;
public:
    QVector3D center;
    float radius;
    Material material;
};
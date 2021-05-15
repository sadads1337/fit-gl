
#include <QVector3D>
#include "Types.hpp"
#include "Material.hpp"

class Sphere {
public:
    Sphere(const QVector3D &c, float r, Material m);
    bool intersect(const Ray &ray, float &t) const;
public:
    QVector3D center;
    float radius;
    Material material;
};
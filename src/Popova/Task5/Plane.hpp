
#include <QVector3D>
#include "Types.hpp"
#include "Material.hpp"

class Plane {
public:
    bool intersect(const Ray &ray, float &t) const;
public:
    QVector3D position;
    QVector3D normal;
    Material material;
};
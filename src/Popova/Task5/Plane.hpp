
#include <QVector3D>
#include "Types.hpp"
#include "Material.hpp"

class Plane {
public:
    Plane(const QVector3D &p,const QVector3D &n, Material m);
    bool intersect(const Ray &ray, float &t) const;
public:
    QVector3D position;
    QVector3D normal;
    Material material;
};
#include "figureinformation.h"

namespace geometry {

QVector<VertexData> FigureInformation::getVertexes() const noexcept{
    return this->gVertexes;
}
QVector<GLushort> FigureInformation::getIndexes() const noexcept{
    return this->gIndexes;
}

QVector3D geometry::FigureInformation::getRotationAxis() const noexcept{
    return this->rotationAxis;
}

QVector3D FigureInformation::getCenter() const noexcept
{
    return this->center_;
}
}

#include "figureinformation.h"

namespace geometry {

QVector<QVector3D> FigureInformation::getVertexes() const noexcept{
    return this->gVertexes;
}
QVector<GLint> FigureInformation::getIndexes() const noexcept{
    return this->gIndexes;
}

void geometry::FigureInformation::setColor(const QVector3D rgb){
    float r = 0;
    float g = 0;
    float b = 0;;
    if (rgb.x() > 1.0)
        r = rgb.x() / 255;
    if (rgb.y() > 1.0)
        g = rgb.y() / 255;
    if (rgb.z() > 1.0)
        b = rgb.z() / 255;
    this->Color={r, g, b, 1};
}

QVector4D geometry::FigureInformation::getColor() const noexcept{
    return this->Color;
}

QVector3D geometry::FigureInformation::getRotationAxis() const noexcept{
    return this->rotationAxis;
}

void geometry::FigureInformation::setRotationAxis(const QVector3D rAxis){
    this->rotationAxis = QVector3D(rAxis.x(), rAxis.y(), rAxis.z());
}

}

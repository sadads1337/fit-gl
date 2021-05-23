#include "figure.hpp"

namespace geometry{


QVector<QVector3D> figure::getVertexes(){
    return this->gVertexes;
}
QVector<GLint> figure::getIndexes(){
    return this->gIndexes;
}

void figure::setColor(QVector3D rgb){
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

QVector4D figure::getColor(){
    return this->Color;
}

QVector3D figure::getRotationAxis(){
    return this->rotationAxis;
}

void figure::setRotationAxis(QVector3D rAxis){
    this->rotationAxis = QVector3D(rAxis.x(), rAxis.y(), rAxis.z());
}
}

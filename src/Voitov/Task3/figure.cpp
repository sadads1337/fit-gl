#include "figure.hpp"

namespace geometry{

VertexData::VertexData(QVector3D position, QVector3D normal){
    this->position = position;
    this->norm = normal;
}

QVector<VertexData> figure::getVertexes(){
    return this->gVertexes;
}
QVector<GLushort> figure::getIndexes(){
    return this->gIndexes;
}

QVector3D figure::getRotationAxis(){
    return this->rotationAxis;
}

QVector3D figure::getCenter(){
    return this->center;
}
}

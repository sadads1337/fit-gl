#include "figure.hpp"

namespace geometry{

VertexData::VertexData(QVector3D position, QVector3D normal){
    this->position = position;
    this->norm = normal;
}
}

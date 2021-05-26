#include "cube.hpp"


void geometry::Cube::init(float width)
{
    this->vBuf.create();
    this->indBuf.create();

    this->half_width = width / 2.0f;

    //initialize block
    {
    gVertexes.append(QVector3D(-this->half_width, -this->half_width, this->half_width));
    gVertexes.append(QVector3D(this->half_width,  -this->half_width, this->half_width));
    gVertexes.append(QVector3D(-this->half_width,  this->half_width, this->half_width));
    gVertexes.append(QVector3D(this->half_width,   this->half_width, this->half_width));
    gVertexes.append(QVector3D(this->half_width,  -this->half_width,-this->half_width));
    gVertexes.append(QVector3D(this->half_width,   this->half_width,-this->half_width));
    gVertexes.append(QVector3D(-this->half_width, -this->half_width,-this->half_width));
    gVertexes.append(QVector3D(-this->half_width,  this->half_width,-this->half_width));

    gIndexes.append(0);
    gIndexes.append(1);
    gIndexes.append(2);
    gIndexes.append(2);
    gIndexes.append(1);
    gIndexes.append(3);//z+
    gIndexes.append(7);
    gIndexes.append(2);
    gIndexes.append(5);
    gIndexes.append(5);
    gIndexes.append(2);
    gIndexes.append(3);//y+
    gIndexes.append(3);
    gIndexes.append(1);
    gIndexes.append(5);
    gIndexes.append(5);
    gIndexes.append(1);
    gIndexes.append(4);//x+
    gIndexes.append(4);
    gIndexes.append(1);
    gIndexes.append(6);
    gIndexes.append(6);
    gIndexes.append(1);
    gIndexes.append(0);//y-
    gIndexes.append(0);
    gIndexes.append(2);
    gIndexes.append(6);
    gIndexes.append(6);
    gIndexes.append(2);
    gIndexes.append(7);//x-
    gIndexes.append(7);
    gIndexes.append(5);
    gIndexes.append(6);
    gIndexes.append(6);
    gIndexes.append(5);
    gIndexes.append(4);//z-
    }
}


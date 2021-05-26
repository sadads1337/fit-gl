#pragma once
#include "figureinformation.h"

namespace geometry{

class Cube final: public FigureInformation {
public:
    void init(GLfloat width, QVector3D center);
private:
    GLfloat width = 1.0;
};
}

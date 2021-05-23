#pragma once
#include "figure.hpp"

namespace geometry{

class Cube final: public figure {
public:
    void init(GLfloat width, QVector3D center);
private:
    GLfloat width = 1.0;
};
}

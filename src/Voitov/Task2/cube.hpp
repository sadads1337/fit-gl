#pragma once
#include "figureinformation.h"

namespace geometry{

class Cube final: public FigureInformation {
public:
    void init(GLfloat width, GLuint N);
private:
    GLfloat half_width = 1.0;
    GLuint num_of_vertixes = 8;
};
}

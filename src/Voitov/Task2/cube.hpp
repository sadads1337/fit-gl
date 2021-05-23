#pragma once
#include "figure.hpp"

namespace geometry{

class Cube final: public figure {
public:
    void init(GLfloat width, GLuint N);
private:
    GLfloat width = 1.0;
    GLuint num_of_vertixes = 8;
};
}

#pragma once
#include "figure.hpp"

namespace geometry{

class Cube final: public figure {
public:
    //Cube();
public:
    void init(float width);
private:
    float width = 1.0;
};
}

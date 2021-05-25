#pragma once
#include "figureinformation.h"

namespace geometry{

class Cube final: public FigureInformation {
public:
    void init(float width);
private:
    float width = 1.0;
};
}

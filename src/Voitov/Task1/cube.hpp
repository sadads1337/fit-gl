#pragma once
#include "figureinformation.h"

namespace geometry{

class Cube final: public FigureInformation {
public:
    void init(float width);
private:
    float half_width = 1.0;
};
}

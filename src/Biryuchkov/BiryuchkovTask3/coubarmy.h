#ifndef COUBARMY_H
#define COUBARMY_H

#include "coub.h"

class coubArmy
{
public:
    coubArmy();

    const std::vector<GLfloat>& getVertex();

    void setCoub(const Coub& cube);
    long long unsigned int vertexCount();

    void setCol(int c);
    void setRow(int r);

    void makeArmy();
private:
    long long unsigned int rows = 1;
    long long unsigned int cols = 1;

    GLfloat dist = 3.0f;

    std::vector<GLfloat> vert ={};

    Coub origin;
};

#endif // COUBARMY_H

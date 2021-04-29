#ifndef COUBARMY_H
#define COUBARMY_H

#include "coub.h"

class coubArmy
{
public:
    coubArmy();

    const std::vector<GLfloat>& getVertex();

    void setCoub(const Coub& cube);
    [[nodiscard]] std::uint64_t vertexCount() const noexcept;

    void setCol(int c);
    void setRow(int r);

     void makeArmy();
private:
    std::uint64_t rows = 1;
    std::uint64_t cols = 1;

    GLfloat dist = 3.0f;

    std::vector<GLfloat> vert ={};

    Coub origin;
};

#endif // COUBARMY_H

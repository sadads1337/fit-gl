#include "coubarmy.h"

coubArmy::coubArmy()
{
    makeArmy();
}

size_t coubArmy::vertexCount()
{
    return vert.size();
}

const std::vector<GLfloat>& coubArmy::getVertex()
{
    return vert;
}

void coubArmy::setCoub(const Coub& cube)
{
    origin = cube;
}

void coubArmy::setCol(int c)
{
    cols =c;
}

void coubArmy::setRow(int r)
{
    rows = r;
}

void coubArmy::makeArmy()
{
    vert.clear();
    for ( long long unsigned int i = 0 ; i < cols;i++)
    {
        vert.insert(vert.end(), origin.getVertex().begin(), origin.getVertex().end());
    }

    GLfloat pos_s = 0;
    if (cols % 2 == 0)
    {
        pos_s = -(cols/2-1)*dist - dist/2;
    }
    else
    {
        pos_s = -(cols-1)/2*dist;
    }

    GLfloat pos = pos_s;
    for (long long unsigned int i = 0 ; i < cols*origin.vertexCount() ; i += origin.vertexCount())
    {
        for (long long unsigned int k = 0 ; k < origin.vertexCount(); k += 3 )
        {
            vert[i + k] +=pos ;
        }
        pos += dist;
    }


}







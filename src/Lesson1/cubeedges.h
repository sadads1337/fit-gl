#ifndef CUBEEDGES_H
#define CUBEEDGES_H

#include "CubeObject.h"

class CubeEdges final: public CubeObject
{
public:
    CubeEdges() = delete;
    explicit CubeEdges(GLfloat edgeLen) : CubeObject(edgeLen, 16){}

    void setColor(const QColor& color) override;

private:
    void setVertices() override;
    void drawArrays() override;
};

#endif // CUBEEDGES_H

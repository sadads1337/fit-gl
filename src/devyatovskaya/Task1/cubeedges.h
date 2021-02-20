#pragma once

#include "CubeObject.h"

class CubeEdges final: public CubeObject
{
public:
    explicit CubeEdges(GLfloat edgeLen) : CubeObject(edgeLen, 16) {}

    void setColor(const QColor& color) override;

private:
    void setVertices() override;
    void drawArrays() override;
};

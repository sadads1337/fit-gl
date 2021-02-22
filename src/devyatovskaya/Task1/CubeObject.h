#pragma once

#include "plainobject3d.h"

class CubeObject : public PlainObject3D
{
public:
        CubeObject(GLfloat edgeLen, GLuint verticesCnt) : edgeLen_(edgeLen) {
        verticesCount = verticesCnt;
        vertices_.resize(verticesCount * 3);
        colors_.resize(verticesCount * 3);
    }

protected:
    GLfloat edgeLen_;
};

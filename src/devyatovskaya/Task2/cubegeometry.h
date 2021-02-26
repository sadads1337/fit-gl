#pragma once
#include "CubicGeometry.h"

class CubeGeometry : public CubicGeometry
{

public:
    CubeGeometry() = delete;
    explicit CubeGeometry(const GLfloat edge_len) : CubicGeometry(edge_len, 18) {}

    void DrawGeometry(QOpenGLShaderProgram* program) override;
    void InitGeometry() override;


private:
    void setVertices() override;
    void setColor() override;
};

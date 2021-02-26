#pragma once
#include "CubicGeometry.h"

class CubeEdges : public CubicGeometry
{

public:
    CubeEdges() = delete;
    explicit CubeEdges(const GLfloat edge_len) : CubicGeometry(edge_len, 16) {}

    void DrawGeometry(QOpenGLShaderProgram* program) override;
    void InitGeometry() override;


private:
    void setVertices() override;
    void setColor() override;
};

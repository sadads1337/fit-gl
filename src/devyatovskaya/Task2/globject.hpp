#pragma once
#include <QOpenGLShaderProgram>

class GLObject
{
public:
    virtual void draw(QOpenGLShaderProgram& program) = 0;
};


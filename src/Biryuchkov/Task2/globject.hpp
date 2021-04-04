#pragma once
#include <QOpenGLShaderProgram>

class GLObject
{
public:
  virtual ~GLObject() = default;
  virtual void draw(QOpenGLShaderProgram& program) = 0;
};


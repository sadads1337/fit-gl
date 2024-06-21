#pragma once

#include "object.hpp"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <memory>

class RenderObject;
using RenderObjectSPtr = std::shared_ptr<RenderObject>;

class RenderObject : public Object {
public:
  ~RenderObject() override = default;
  virtual void render(QOpenGLFunctions &functions) = 0;
  virtual void
  initialize(std::shared_ptr<QOpenGLShaderProgram> pShaderProgram) = 0;
  virtual RenderObjectSPtr clone() const { return {nullptr}; }
};

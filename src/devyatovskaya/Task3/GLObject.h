#pragma once
#include "GLMaterial.h"
#include "GLMeshRenderer.h"
#include "GLTexture.h"
#include "GLTransform.h"
#include <memory>

class GLObject {
public:
  GLMesh mesh;
  GLTransform transform;
  GLMaterial material;
  std::shared_ptr<GLMeshRenderer> renderer;

  void
  init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program) const;
};

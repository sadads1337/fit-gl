#pragma once
#include <memory>
struct GLMaterial;
class GLMeshRenderer;
class GLMesh;
class GLTransform;

class GLMeshRendererGenerator {
public:
  virtual std::shared_ptr<GLMeshRenderer> get_renderer(GLMesh &, GLTransform &,
                                                       GLMaterial &) = 0;
  virtual ~GLMeshRendererGenerator() = default;
};
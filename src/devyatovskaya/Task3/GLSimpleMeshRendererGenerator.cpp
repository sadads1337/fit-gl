#include "GLSimpleMeshRendererGenerator.h"

std::shared_ptr<GLMeshRenderer> GLSimpleMeshRendererGenerator::get_renderer(
    GLMesh &mesh, GLTransform &transform, GLMaterial &material) {
  return std::make_shared<GLSimpleMeshRenderer>(mesh, transform, material);
}

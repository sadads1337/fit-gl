#include "TesselatedRenderable.hpp"
namespace Kononov {

void TesselatedRenderable::render(Camera camera, QMatrix4x4 model_matrix) {
  GL::requireFunctions40core()->glPatchParameteri(GL_PATCH_VERTICES,
                                                  m_patch_vertices);
  GenericRenderable::render(camera, model_matrix);
}

} // namespace Kononov
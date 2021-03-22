#pragma once

#include <Renderable.hpp>
namespace Kononov {

class TesselatedRenderable : public GenericRenderable {
private:
  int m_patch_vertices;

public:
  template <typename VertexInterface, typename VertexType>
  TesselatedRenderable(
      const std::shared_ptr<TypedShader<VertexInterface>> &shader,
      const std::shared_ptr<TypedMesh<VertexType>> &mesh, int path_vertices)
      : GenericRenderable(shader, mesh), m_patch_vertices(path_vertices) {}

  void render(Camera camera, QMatrix4x4 model_matrix) override;
};
} // namespace Kononov
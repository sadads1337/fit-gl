#pragma once

#include "material.hpp"
#include "meshobject.hpp"

#include <QMatrix4x4>

class SceneObject : public MeshObject {
  using MaterialSPrt = std::shared_ptr<Material>;
  MaterialSPrt material_;

public:
  SceneObject(MeshSPtr mesh, QMatrix4x4 const &model_matrix,
              MaterialSPrt material);
  void render(QOpenGLFunctions &functions) override;
  RenderObjectSPtr clone() const override;
};

#pragma once

#include "lightsource.hpp"
#include "meshobject.hpp"

class PointLightSource : public MeshObject, public LightSource {

public:
  QVector3D position;
  float constFactor;
  float linFactor;
  float quadFactor;

  ~PointLightSource() override = default;

  PointLightSource(MeshSPtr mesh, QMatrix4x4 const &model_matrix,
                   QVector3D const &color = {1.f, 1.f, 1.f},
                   float intensity = 1.f, float constFactor = 1.f,
                   float linFactor = 0.045f, float quadFactor = 0.015f);

  void render(QOpenGLFunctions &functions) override;
  void uploadToShader(ShaderProgSPtr pShader, size_t index) override;
  void offsetMove(QVector3D const &offset) override;
};

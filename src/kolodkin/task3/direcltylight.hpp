#pragma once

#include "lightsource.hpp"

class DirecltyLight : public LightSource {
public:
  QVector3D direction;

  DirecltyLight(QVector3D const &color, float intensity,
                QVector3D const &direction);
  ~DirecltyLight() override = default;
  void uploadToShader(std::shared_ptr<QOpenGLShaderProgram> shader,
                      size_t index) override;
};

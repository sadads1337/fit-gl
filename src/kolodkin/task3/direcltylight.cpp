#include "direcltylight.hpp"

#include <string>

DirecltyLight::DirecltyLight(const QVector3D &color, float intensity,
                             const QVector3D &_direction)
    : LightSource(color, intensity), direction(_direction) {}

void DirecltyLight::uploadToShader(std::shared_ptr<QOpenGLShaderProgram> shader,
                                   size_t index) {
  shader->bind();
  shader->setUniformValue(
      ("dirLights[" + std::to_string(index) + "].color").c_str(), color);
  shader->setUniformValue(
      ("dirLights[" + std::to_string(index) + "].intensity").c_str(),
      intensity);
  shader->setUniformValue(
      ("dirLights[" + std::to_string(index) + "].direction").c_str(),
      direction);
}

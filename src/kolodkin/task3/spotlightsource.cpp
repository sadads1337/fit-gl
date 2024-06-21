#include "spotlightsource.hpp"

SpotLightSource::SpotLightSource(const QVector3D &position,
                                 const QVector3D &direction,
                                 QVector3D const &color, float intensity,
                                 float cutOff, float outerCutOff,
                                 float constFact, float linFact, float quadFact)
    : LightSource(color, intensity), position_(position), direction_(direction),
      cutOff(cutOff), outerCutOff(outerCutOff), constFactor(constFact),
      linFactor(linFact), quadFactor(quadFact) {}

void SpotLightSource::uploadToShader(
    std::shared_ptr<QOpenGLShaderProgram> pShader, size_t index) {
  pShader->bind();
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].color").c_str(), color);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].position").c_str(),
      position_);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].direction").c_str(),
      direction_);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].intensity").c_str(),
      intensity);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].constFactor").c_str(),
      constFactor);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].linFactor").c_str(),
      linFactor);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].quadFactor").c_str(),
      quadFactor);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].cutOff").c_str(), cutOff);
  pShader->setUniformValue(
      ("spotLights[" + std::to_string(index) + "].outerCutOff").c_str(),
      cutOff + outerCutOff + 0.0001f);
}

void SpotLightSource::offsetMove(const QVector3D &offset) {
  position_ += offset;
}

void SpotLightSource::moveTo(const QVector3D &position) {
  position_ = position;
}

void SpotLightSource::setDirection(const QVector3D &direction) {
  direction_ = direction;
}

#include "pointlightsource.hpp"

PointLightSource::PointLightSource(MeshSPtr mesh,
                                   QMatrix4x4 const &model_matrix,
                                   QVector3D const &color, float intensity,
                                   float _constFactor, float _linFactor,
                                   float _quadFactor)
    : MeshObject(std::move(mesh), model_matrix), LightSource(color, intensity),
      position(model_matrix.column(3)), constFactor(_constFactor),
      linFactor(_linFactor), quadFactor(_quadFactor) {}

void PointLightSource::render(QOpenGLFunctions &functions) {
  pShaderProgram_->bind();
  pShaderProgram_->setUniformValue("lightColor", color);

  MeshObject::render(functions);
}

void PointLightSource::uploadToShader(MeshObject::ShaderProgSPtr pShader,
                                      size_t index) {
  pShader->bind();
  pShader->setUniformValue(
      ("pointLights[" + std::to_string(index) + "].color").c_str(), color);
  pShader->setUniformValue(
      ("pointLights[" + std::to_string(index) + "].position").c_str(),
      position);
  pShader->setUniformValue(
      ("pointLights[" + std::to_string(index) + "].intensity").c_str(),
      intensity);
  pShader->setUniformValue(
      ("pointLights[" + std::to_string(index) + "].constFactor").c_str(),
      constFactor);
  pShader->setUniformValue(
      ("pointLights[" + std::to_string(index) + "].linFactor").c_str(),
      linFactor);
  pShader->setUniformValue(
      ("pointLights[" + std::to_string(index) + "].quadFactor").c_str(),
      quadFactor);
}

void PointLightSource::offsetMove(const QVector3D &offset) {
  position = QVector3D(getModel().column(3));
  MeshObject::offsetMove(offset);
}

#include "GLDirectedLight.h"

GLDirectedLight::GLDirectedLight(QVector3D _position, QColor _color,
                                 const float _intensity)
    : GLLightSource{std::move(_position), std::move(_color), _intensity} {}

void GLDirectedLight::upload_to_shader(
    const std::shared_ptr<QOpenGLShaderProgram> &shader, const size_t index) {
  shader->setUniformValue(
      ("directed_lights[" + std::to_string(index) + "].direction").c_str(),
      position);
  shader->setUniformValue(
      ("directed_lights[" + std::to_string(index) + "].color").c_str(), color);
  shader->setUniformValue(
      ("directed_lights[" + std::to_string(index) + "].intensity").c_str(),
      intensity);
}

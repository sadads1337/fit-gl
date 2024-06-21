#pragma once
#include <QOpenGLShaderProgram>
#include <memory>

class LightSource {
public:
  QVector3D color{1.f, 1.f, 1.f};
  float intensity = 1.f;

  LightSource(QVector3D const &_color, float _intensity)
      : color(_color), intensity(_intensity) {}

  virtual ~LightSource() = default;

  virtual void uploadToShader(std::shared_ptr<QOpenGLShaderProgram> shader,
                              size_t index) = 0;
};

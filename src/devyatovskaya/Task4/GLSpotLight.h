#pragma once
#include "GLLightSource.h"

class GLSpotLight final : public GLLightSource {
public:
  QVector3D direction;
  float cutOff;
  float outerCutOff;

  GLSpotLight(QVector3D _position, QColor _color,
              QVector3D _direction = QVector3D(0, -1, 0), float _intensity = 1);

  void upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram> &shader,
                        size_t index) override;
};
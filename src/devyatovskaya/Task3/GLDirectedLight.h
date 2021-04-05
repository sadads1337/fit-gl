#pragma once
#include "GLLightSource.h"

class GLDirectedLight final : public GLLightSource
{
public:

	GLDirectedLight(QVector3D _position, QColor _color, float _intensity = 2.f);
	void upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, size_t index) override;
};
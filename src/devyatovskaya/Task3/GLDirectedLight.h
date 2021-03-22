#pragma once
#include "GLLightSource.h"

class GLDirectedLight final : public GLLightSource
{
public:

	GLDirectedLight(const QVector3D& _position, const QColor& _color, const float _intensity = 2.f)
		: GLLightSource{ _position , _color, _intensity }
	{

	}

	void upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, const size_t index) override
	{
		shader->setUniformValue(("directed_lights[" + std::to_string(index) + "].direction").c_str(), position);
		shader->setUniformValue(("directed_lights[" + std::to_string(index) + "].color").c_str(), color);
		shader->setUniformValue(("directed_lights[" + std::to_string(index) + "].intensity").c_str(), intensity);
	}
};
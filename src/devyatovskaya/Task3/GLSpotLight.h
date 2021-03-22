#pragma once
#include <qmath.h>

#include "GLLightSource.h"

class GLSpotLight final : public GLLightSource
{
public:
	float cutOff = 16.5;
	float outerCutOff = 55.5;

	QVector3D direction;
	GLSpotLight(const QVector3D& _position, const QColor& _color, const QVector3D& _direction = QVector3D(0, -1, 0), float _intensity = 1)
		:	GLLightSource(_position, _color, _intensity),
			direction(_direction)
	{
	}

	void upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, const size_t index) override
	{
		shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].position").c_str(), position);
		shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].color").c_str(), color);
		shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].direction").c_str(), direction);

        shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].cutOff").c_str(), cos(qDegreesToRadians(cutOff)));
        shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].outerCutOff").c_str(), cos(qDegreesToRadians(outerCutOff)));
		shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].intensity").c_str(), intensity);

	}
};

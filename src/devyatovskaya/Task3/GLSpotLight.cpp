#include <qmath.h>
#include "GLSpotLight.h"


GLSpotLight::GLSpotLight(QVector3D _position, QColor _color, QVector3D _direction, float _intensity)
	:	GLLightSource(std::move(_position), std::move(_color), _intensity),
		direction(std::move(_direction)),
		cutOff{ 16.5f },
		outerCutOff{55.5f}
{
}

void GLSpotLight::upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, const size_t index)
{
	shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].position").c_str(), position);
	shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].color").c_str(), color);
	shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].direction").c_str(), direction);

    shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].cutOff").c_str(), float(cos(qDegreesToRadians(cutOff))));
    shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].outerCutOff").c_str(),float( cos(qDegreesToRadians(outerCutOff))));
	shader->setUniformValue(("spot_lights[" + std::to_string(index) + "].intensity").c_str(), intensity);
}

#include "GLPointLight.h"


GLPointLight::GLPointLight(QVector3D _position, QColor _color, const float _intensity)
	:	GLLightSource{ std::move(_position) ,std::move(_color), _intensity }
{
	
}


void GLPointLight::upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, const size_t index)
{
	shader->setUniformValue(("point_lights[" + std::to_string(index) + "].position").c_str(), position);
	shader->setUniformValue(("point_lights[" + std::to_string(index) + "].color").c_str(), color);
	shader->setUniformValue(("point_lights[" + std::to_string(index) + "].intensity").c_str(), intensity);
}

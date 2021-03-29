#pragma once
#include <QOpenGLShaderProgram>
#include <QColor>

#include "GLMaterial.h"

class GLLightSource
{
public:
	QVector3D position;
	QColor color;
	float intensity;

	GLLightSource(QVector3D _position, QColor _color, float _intensity);

	
	virtual ~GLLightSource() = default;
	virtual void upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, size_t index) = 0;
};

using light_sptr = std::shared_ptr<GLLightSource>;
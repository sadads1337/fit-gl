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

	GLLightSource(const QVector3D& _position, const QColor& _color, const float _intensity)
		:	position{ _position },
			color{ _color },
			intensity{ _intensity }
	{
		
	}

	
	virtual ~GLLightSource() = default;
	virtual void upload_to_shader(const std::shared_ptr<QOpenGLShaderProgram>& shader, size_t index) = 0;
};

using light_sptr = std::shared_ptr<GLLightSource>;
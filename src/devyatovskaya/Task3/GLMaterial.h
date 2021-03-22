#pragma once
#include <QColor>
#include <QOpenGLShaderProgram>
#include "GLTexture.h"


struct GLMaterial
{
	GLTexture texture;
	bool is_light_source = false;
	QColor ambient;
	QColor diffuse;
	QColor specular;
	float  shininess{ 0 };

	GLMaterial(const bool _is_light_source = false, const QColor& _ambient = {}, const QColor& _diffuse = {}, const QColor& _specular = {}, float _shininess = 0)
		:	is_light_source{ _is_light_source },
			ambient{ _ambient },
			diffuse{ _diffuse },
			specular{ _specular },
			shininess{ _shininess }
	{
		
	}
	
	void upload_to_shader(std::shared_ptr<QOpenGLShaderProgram>& shader) const
	{
		shader->setUniformValue("material.ambient", ambient);
		shader->setUniformValue("material.diffuse", diffuse);
		shader->setUniformValue("material.specular", ambient);
		shader->setUniformValue("material.shininess", shininess);
	}
};

#include "GLMaterial.h"




GLMaterial::GLMaterial(QColor _ambient, QColor _diffuse, QColor _specular, float _shininess, bool _is_light_source)
	:	ambient{ std::move(_ambient) },
		diffuse{ std::move(_diffuse) },
		specular{ std::move(_specular) },
		shininess{ _shininess },
		is_light_source{ _is_light_source }
{
	
}


void GLMaterial::upload_to_shader(std::shared_ptr<QOpenGLShaderProgram>& shader) const
{
	shader->setUniformValue("material.ambient", ambient);
	shader->setUniformValue("material.diffuse", diffuse);
	shader->setUniformValue("material.specular", ambient);
	shader->setUniformValue("material.shininess", shininess);
}

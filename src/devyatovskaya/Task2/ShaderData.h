#pragma once
#include <string>
#include <QOpenGLShaderProgram>

#include "GLMeshRendererGenerator.h"


struct ShaderData final
{
	std::string vertex;
	std::string fragment;
	std::shared_ptr<GLMeshRendererGenerator> renderer_generator;
	std::shared_ptr<QOpenGLShaderProgram> shader_program{ nullptr };

	std::shared_ptr<QOpenGLShaderProgram> get_shader_program();
};

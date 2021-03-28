#pragma once
#include <memory>
#include "GLMeshRenderer.h"
#include "GLTransform.h"


class GLObject
{
public:
	GLMesh mesh;
	GLTransform transform;
	std::shared_ptr<GLMeshRenderer> renderer;

	void init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program) const;
};

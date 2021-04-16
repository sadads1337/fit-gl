#pragma once
#include <memory>
#include "GLMaterial.h"
#include "GLMeshRenderer.h"
#include "GLTransform.h"
#include "GLTexture.h"


class GLObject
{
public:
	GLMesh mesh;
	GLTransform transform;
	GLMaterial material;
	std::shared_ptr<GLMeshRenderer> renderer;

	void init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program) const;
};

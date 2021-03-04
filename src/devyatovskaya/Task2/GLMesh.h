#pragma once
#include <vector>
#include <QOpenGLShaderProgram>
#include <memory>
#include "GLVertex.h"

class GLMesh
{
public:
	GLMesh() = default;
	GLMesh(std::vector<GLVertex> v, std::vector<unsigned> i);

	
	std::vector<GLVertex> vertices{};
	std::vector<unsigned> indices{};
};

#pragma once
#include <vector>

#include "GLVertex.h"
class GLMesh
{
public:
	GLMesh() = default;
	GLMesh(std::vector<GLVertex> _vertices, std::vector<unsigned> _indices);

	std::vector<GLVertex> vertices;
	std::vector<unsigned> indices;
};

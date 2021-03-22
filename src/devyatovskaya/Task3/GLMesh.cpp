#include "GLMesh.h"

#include <utility>

GLMesh::GLMesh(std::vector<GLVertex> _vertices, std::vector<unsigned> _indices)
	: vertices{std::move(_vertices)}, indices{std::move(_indices)}
{
}

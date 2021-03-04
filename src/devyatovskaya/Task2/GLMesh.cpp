#include "GLMesh.h"

#include <utility>

GLMesh::GLMesh(std::vector<GLVertex> v, std::vector<unsigned> i)
	: vertices{std::move(v)}, indices{std::move(i)}
{
}

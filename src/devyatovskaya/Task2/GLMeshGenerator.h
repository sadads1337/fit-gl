#pragma once
#include "GLMesh.h"

class GLMeshGenerator
{
public:
	GLMeshGenerator() = default;
	
	virtual GLMesh generate(std::size_t mesh_steps) const = 0;
	virtual GLMesh generate() const = 0;
	
	virtual ~GLMeshGenerator() = default;
};

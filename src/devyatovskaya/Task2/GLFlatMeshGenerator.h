#pragma once
#include "GLMeshGenerator.h"

class GLFlatMeshGenerator : public GLMeshGenerator
{
public:
	explicit GLFlatMeshGenerator(float edge_len);


	GLMesh generate(std::size_t mesh_steps) const override;

private:
	float edge_len_;
	void init_vertices(std::vector<GLVertex>& vertices, std::size_t mesh_steps) const;
	void init_indices(std::vector<unsigned>& indices, std::size_t mesh_steps) const;

	GLMesh generate() const override;
};

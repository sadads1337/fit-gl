#pragma once
#include "GLMeshGenerator.h"

class GLSphereMeshGenerator : public GLMeshGenerator
{
public:
	explicit GLSphereMeshGenerator(float radius, std::size_t sector_count, std::size_t stack_count);
	
	GLMesh generate(const QColor& color) const override;

	float radius_;
	std::size_t sector_count_;
	std::size_t stack_count_;
private:
	void init_vertices(std::vector<GLVertex>& vertices, const QColor& color) const override;
    void init_indices(std::vector<unsigned>& indices) const override;
};

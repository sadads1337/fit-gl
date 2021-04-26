#pragma once
#include "GLMeshGenerator.h"



class GLFlatMeshGenerator : public GLMeshGenerator
{
public:
	GLFlatMeshGenerator(float edge_len, unsigned steps_count);


	GLMesh generate(const QColor& color) const override;
	unsigned step_count() const;
	
private:
	float edge_len_;
	unsigned step_count_;

	void init_vertices(std::vector<GLVertex>& vertices, const QColor& color) const override;
	void init_indices(std::vector<unsigned>& indices) const override;
};

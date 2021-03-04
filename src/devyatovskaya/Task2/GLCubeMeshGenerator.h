#pragma once
#include "GLMeshGenerator.h"
#include "GLFlatMeshGenerator.h"

class GLCubeMeshGenerator : public GLMeshGenerator
{
public:
	explicit GLCubeMeshGenerator(float edge_len);


	GLMesh generate(std::size_t mesh_steps) const override;

private:
	GLFlatMeshGenerator face_generator_;
	GLMesh generate() const override;


	void rotate_face(std::vector<GLVertex>& plane_vertices, const QMatrix4x4& matrix) const;

	void get_side_faces(std::vector<GLVertex>& plane_vertices, std::vector<GLVertex>& cube_vertices, QMatrix4x4& matrix) const;
	void get_top_n_bottom(std::vector<GLVertex>& plane_vertices, std::vector<GLVertex>& cube_vertices, QMatrix4x4& matrix) const;
};

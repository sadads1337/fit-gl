#pragma once
#include "GLMeshGenerator.h"
#include "GLFlatMeshGenerator.h"

class GLCubeMeshGenerator : public GLMeshGenerator
{
public:
    explicit GLCubeMeshGenerator(float edge_len, unsigned steps_count);

	GLMesh generate(const QColor& color) const override;
private:
	GLFlatMeshGenerator face_generator_;

	void rotate_face(std::vector<GLVertex>& plane_vertices, const QMatrix4x4& matrix) const;
	void get_side_faces(std::vector<GLVertex>& plane_vertices, 
						std::vector<GLVertex>& cube_vertices, 
						QMatrix4x4& matrix) const;
	void get_top_n_bottom(std::vector<GLVertex>& plane_vertices, 
						  std::vector<GLVertex>& cube_vertices, 
						  QMatrix4x4& matrix) const;

	void init_indices(std::vector<unsigned>& indices) const override;
	void init_vertices(std::vector<GLVertex>& vertices, const QColor& color) const override;
};

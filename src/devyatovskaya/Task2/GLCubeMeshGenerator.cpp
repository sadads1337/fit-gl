#include <algorithm>
#include "GLCubeMeshGenerator.h"
#include "QMatrix4x4"

GLCubeMeshGenerator::GLCubeMeshGenerator(const float edge_len, const std::size_t steps_count)
	: face_generator_{ edge_len, steps_count }
{
}
GLMesh GLCubeMeshGenerator::generate(const QColor& color) const
{
	auto front_face = face_generator_.generate(color);
	auto cube_vertices = front_face.vertices;

	QMatrix4x4 rotation;
	get_side_faces(front_face.vertices, cube_vertices, rotation);
	get_top_n_bottom(front_face.vertices, cube_vertices, rotation);

	auto cube_indices = front_face.indices;

	const auto number_of_faces = 6u;

	for (auto i = 1u; i < number_of_faces; ++i) {
		std::copy(front_face.indices.begin(), front_face.indices.end(), std::back_inserter(cube_indices));

		std::for_each(cube_indices.begin() + i * front_face.indices.size(), cube_indices.end(), [&](auto& index)
		{
				index += static_cast<unsigned>(i * front_face.vertices.size());
		});
	}

	return { cube_vertices, cube_indices };
}


void GLCubeMeshGenerator::rotate_face(std::vector<GLVertex>& plane_vertices, const QMatrix4x4& matrix) const
{
	std::for_each(plane_vertices.begin(), plane_vertices.end(), [&](GLVertex& vertex)
	{
		vertex.coordinate = matrix * vertex.coordinate;
		vertex.normal = matrix * vertex.normal;
		// ?
		vertex.tangent = matrix * vertex.tangent;
		vertex.bitangent = matrix * vertex.bitangent;
		
	});
}


void GLCubeMeshGenerator::get_side_faces(std::vector<GLVertex>& plane_vertices, 
										 std::vector<GLVertex>& cube_vertices, 
										 QMatrix4x4& matrix) const
{
	const auto side_faces = 4u;

	for (auto i = 0u; i < side_faces - 1; ++i) {
		matrix.rotate(90.f, 0.f, 1.f);
		rotate_face(plane_vertices, matrix);
		std::copy(plane_vertices.begin(), plane_vertices.end(), std::back_inserter(cube_vertices));
	}
}



void GLCubeMeshGenerator::get_top_n_bottom(std::vector<GLVertex>& plane_vertices, 
										   std::vector<GLVertex>& cube_vertices,
										   QMatrix4x4& matrix) const
{
	const auto up_n_bottom_faces = 2u;
	
	for (auto i = 0u; i < up_n_bottom_faces; ++i) {
		matrix.rotate(90.f, 1.f, 0.f);
		rotate_face(plane_vertices, matrix);
		std::copy(plane_vertices.begin(), plane_vertices.end(), std::back_inserter(cube_vertices));
	}
}

void GLCubeMeshGenerator::init_indices([[maybe_unused]]std::vector<unsigned>& indices) const
{
}

void GLCubeMeshGenerator::init_vertices([[maybe_unused]]std::vector<GLVertex>& vertices, [[maybe_unused]] const QColor& color) const
{
}

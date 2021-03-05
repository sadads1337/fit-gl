#include "GLFlatMeshGenerator.h"

GLFlatMeshGenerator::GLFlatMeshGenerator(const float edge_len)
	: edge_len_{ edge_len }
{
}

GLMesh GLFlatMeshGenerator::generate(const std::size_t mesh_steps) const
{
    GLMesh mesh{};
	
    mesh.vertices.reserve((mesh_steps + 1) * (mesh_steps + 1));
    mesh.indices.reserve(6 * mesh_steps * mesh_steps);

    init_vertices(mesh.vertices, mesh_steps);
    unsigned_mesh_steps = static_cast<unsigned>(mesh_steps);
    init_indices(mesh.indices, unsigned_mesh_steps);

    return mesh;
}

GLMesh GLFlatMeshGenerator::generate() const
{
	return GLMesh{};
}

void GLFlatMeshGenerator::init_vertices(std::vector<GLVertex>& vertices, const std::size_t mesh_steps) const
{
    const auto  normalized_step = edge_len_ / static_cast<float>(mesh_steps);
    GLVertex vertex{};
	
    for (std::size_t j = 0; j < mesh_steps + 1; ++j) {
        for (std::size_t i = 0; i < mesh_steps + 1; ++i) {
            vertex.coordinate.setX(-edge_len_ / 2.f + normalized_step * static_cast<float>(i));
            vertex.coordinate.setY(-edge_len_ / 2.f + normalized_step * static_cast<float>(j));
            vertex.coordinate.setZ(edge_len_ / 2.f);

            vertex.color.setX(255);
            vertex.color.setY(0);
            vertex.color.setZ(255);
            vertices.emplace_back(vertex);
        }
    }
}

void GLFlatMeshGenerator::init_indices(std::vector<unsigned>& indices, unsigned mesh_steps) const
{
    for (unsigned j = 0; j < mesh_steps; ++j) {
    	
        for (unsigned i = 0; i < mesh_steps; ++i) {
        	
            auto k = i + (j + 1) * (mesh_steps + 1);
            auto p = i + j * (mesh_steps + 1);
            indices.push_back(k);
            indices.push_back(p);
            indices.push_back(p + 1);

            indices.push_back(p + 1);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
    }
}

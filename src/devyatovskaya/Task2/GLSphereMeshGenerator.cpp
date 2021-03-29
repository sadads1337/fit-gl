#include "GLSphereMeshGenerator.h"
#include <cmath>

GLSphereMeshGenerator::GLSphereMeshGenerator(const float radius, const std::size_t sector_count, const std::size_t stack_count)
	:	radius_{radius},
		sector_count_{sector_count},
		stack_count_{stack_count}
{
	
}


GLMesh GLSphereMeshGenerator::generate(const QColor& color) const
{
	GLMesh mesh{};
	
    init_vertices(mesh.vertices, color);
    init_indices(mesh.indices);
    init_tangent_bitangent_vectors(mesh.vertices, mesh.indices);

	return mesh;
}


void GLSphereMeshGenerator::init_vertices(std::vector<GLVertex>& vertices, const QColor& color) const
{
    const auto PI = atanf(1.0) * 4.f;
	
    const auto sectorStep = 2 * PI / static_cast<float>(sector_count_);
	const auto stackStep = PI / static_cast<float>(stack_count_);
    const auto length_inv = 1.f / radius_;
    GLVertex vertex{};
	
    for (auto i = 0u; i <= stack_count_; ++i)
    {
        const auto stack_angle = PI / 2 - static_cast<float>(i) * stackStep;
        const auto xy = radius_ * cosf(stack_angle);
        const auto z = radius_ * sinf(stack_angle);

        for (auto j = 0u; j <= sector_count_; ++j)
        {
            const auto sector_angle = static_cast<float>(j) * sectorStep;
        	
            const auto x = xy * cosf(sector_angle);
            const auto y = xy * sinf(sector_angle);
            vertex.coordinate = { x, y, z };
            vertex.normal = { x * length_inv , y * length_inv , z * length_inv };
        	
            vertex.color.setX(static_cast<float>(color.redF()));
            vertex.color.setY(static_cast<float>(color.greenF()));
            vertex.color.setZ(static_cast<float>(color.blueF()));

            vertex.texture = { static_cast<float>(j) / sector_count_ , static_cast<float>(i) / stack_count_ };
        	
            vertices.push_back(vertex);

        }
    }
}


void GLSphereMeshGenerator::init_indices(std::vector<unsigned>& indices) const
{
    for (auto i = 0u; i < stack_count_; ++i)
    {
        auto k1 = i * (sector_count_ + 1);
        auto k2 = k1 + sector_count_ + 1;

        for (auto j = 0u; j < sector_count_; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1u);
            }
        	
            if (i != (stack_count_ - 1))
            {
                indices.push_back(k1 + 1u);
                indices.push_back(k2);
                indices.push_back(k2 + 1u);
            }
        }
    }

}

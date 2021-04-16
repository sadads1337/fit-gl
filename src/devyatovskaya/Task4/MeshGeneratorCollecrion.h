#pragma once
#include "GLCubeMeshGenerator.h"
#include "GLSphereMeshGenerator.h"
#include <map>
#include <memory>

constexpr std::size_t initial_grid_step = 10;
// 36
constexpr std::size_t initial_sector_count = 72;
// 18
constexpr std::size_t initial_stack_count = 36;


class MeshGeneratorCollection final
{
public:

	inline static std::map<std::string, std::shared_ptr<GLMeshGenerator>> generators =
	{
        {{"cube"}, std::make_shared<GLCubeMeshGenerator>(1.0f, static_cast<unsigned>(initial_grid_step))},
		{{"sphere"}, std::make_shared<GLSphereMeshGenerator>(1.0f, initial_sector_count, initial_stack_count)}
	};
};

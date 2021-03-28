#include "PreparedScenes.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"

void init_grid(GLScene& scene, ShaderData& data, const size_t grid_size)
{
	const auto& generator = MeshGeneratorCollection::generators["cube"];
	QVector3D pos = {};

	for (std::size_t i = 0; i < grid_size; ++i) {

		for (std::size_t j = 0; j < grid_size; ++j) {
			pos.setX(static_cast<float>(i) * 2.5f);
			pos.setY(-3);
			pos.setZ(static_cast<float>(j) * 2.5f - 10);

            scene.add_object(data, generator, pos, { 185, 255, 208 });
		}
	}
}



void PreparedScenes::init()
{
	scenes.push_back(default_morphing(ShaderCollection::shaders["morphing"]));
}


GLScene PreparedScenes::default_morphing(ShaderData& data)
{
	GLScene scene;
	const auto grid_size = 20u;

	
	init_grid(scene, data, grid_size);
	return scene;
}

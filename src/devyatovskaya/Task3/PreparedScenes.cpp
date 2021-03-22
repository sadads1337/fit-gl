#include "PreparedScenes.h"

#include "GLDirectedLight.h"
#include "GLPointLight.h"
#include "GLSpotLight.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"


void PreparedScenes::init()
{
	scenes.emplace("default", default_scene());

}

GLScene PreparedScenes::default_scene()
{
	GLScene scene;
	auto& shader = ShaderCollection::shaders["guro_lighting"];
	const auto& generator = MeshGeneratorCollection::generators["sphere"];

	GLMaterial material;
	material.shininess = 32.0f;
	scene.add_object(shader, generator, { -1, 0, -1 }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { -1, 0, 1 }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, { 1, 0, 1 }, { 0, 0, 0 }, material);
	scene.add_object(shader, generator, {1, 0, -1}, { 0, 0, 0 }, material);
	

	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];
	const auto light = std::make_shared<GLSpotLight>(QVector3D{ 0, 2, 0 }, QColor{ 255, 255, 255 });
	scene.add_light(light, light_object_shader, light_object_generator);


	return scene;
}

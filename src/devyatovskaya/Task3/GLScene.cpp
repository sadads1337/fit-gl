#include "GLScene.h"
#include "GLDirectedLight.h"
#include "MeshGeneratorCollecrion.h"
#include "GLMeshGenerator.h"
#include "ShaderCollection.h"
#include "GLTextureLoader.h"

obj_sptr GLScene::create_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color, const GLMaterial& material) const
{
	auto object = std::make_shared<GLObject>();
	object->mesh = mesh_generator->generate(color);
	object->transform.translate(pos);
	object->material = material;
	object->renderer = data.renderer_generator->get_renderer(object->mesh, object->transform, object->material);
	object->init_renderer(data.get_shader_program());
	
	return object;
}

obj_sptr GLScene::create_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, [[maybe_unused]] const QColor& color, const GLMaterial& material) const
{
	auto object = std::make_shared<GLObject>();
	object->mesh = mesh;
	object->transform.translate(pos);
	object->material = material;
	object->renderer = data.renderer_generator->get_renderer(object->mesh, object->transform, object->material);
	object->init_renderer(data.get_shader_program());

	return object;
}

void GLScene::add_light(light_sptr light, ShaderData& data, const mesh_gen_sptr& mesh_generator)
{

	lights_objects.emplace(std::move(light), create_object(data, mesh_generator, light->position, light->color, { true }));
}

void GLScene::add_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color, const GLMaterial& material)
{
	objects.push_back(create_object(data, mesh_generator, pos, color, material));
}

void GLScene::add_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color, const GLMaterial& material)
{
	objects.push_back(create_object(data, mesh, pos, color, material));
}

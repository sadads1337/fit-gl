#include "GLScene.h"
#include "MeshGeneratorCollecrion.h"
#include "GLMeshGenerator.h"
#include "ShaderCollection.h"

obj_sptr GLScene::create_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color) const
{
	auto object = std::make_shared<GLObject>();
	object->mesh = mesh_generator->generate(color);
	object->transform.translate(pos);
    object->renderer = data.renderer_generator->get_renderer(object->mesh, object->transform);
	object->init_renderer(data.get_shader_program());
	
	return object;
}

obj_sptr GLScene::create_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color) const
{
	auto object = std::make_shared<GLObject>();
	object->mesh = mesh;
	object->transform.translate(pos);
    object->renderer = data.renderer_generator->get_renderer(object->mesh, object->transform);
	object->init_renderer(data.get_shader_program());

	return object;
}


void GLScene::add_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color)
{
    objects.push_back(create_object(data, mesh_generator, pos, color));
}

void GLScene::add_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color)
{
    objects.push_back(create_object(data, mesh, pos, color));
}

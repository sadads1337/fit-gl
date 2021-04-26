#pragma once
#include "GLObject.h"
#include "GLCameraMover.h"
#include "GLLightSource.h"
class GLMeshGenerator;
using mesh_gen_sptr = std::shared_ptr<GLMeshGenerator>;

class GLScene final
{
public:
	GLCameraMover camera_mover;
	
	std::vector<obj_sptr> objects;
	std::map<light_sptr, obj_sptr> lights_objects;
	
	void add_light(light_sptr light, ShaderData& data, const mesh_gen_sptr& mesh_generator);
	void add_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color, const GLMaterial& material);
	void add_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color, const GLMaterial& material);
private:
	obj_sptr create_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color, const GLMaterial& material) const;
	obj_sptr create_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color, const GLMaterial& material) const;
};

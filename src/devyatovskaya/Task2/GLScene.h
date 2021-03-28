#pragma once
#include "GLObject.h"
#include "GLCameraMover.h"

class GLMeshGenerator;
using mesh_gen_sptr = std::shared_ptr<GLMeshGenerator>;

class GLScene final
{
public:
	GLCameraMover camera_mover;
	
	std::vector<obj_sptr> objects;

    void add_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color);
    void add_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color);
private:
    obj_sptr create_object(ShaderData& data, const mesh_gen_sptr& mesh_generator, const QVector3D& pos, const QColor& color) const;
    obj_sptr create_object(ShaderData& data, const GLMesh& mesh, const QVector3D& pos, const QColor& color) const;
};

#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_0>
#include <map>

#include "GLMesh.h"
#include "GLTransform.h"
#include "ShaderData.h"

struct GLMaterial;
class GLCamera;
class GLObject;
class GLLightSource;

using light_sptr = std::shared_ptr<GLLightSource>;
using obj_sptr = std::shared_ptr<GLObject>;


class GLMeshRenderer : protected QOpenGLFunctions_3_0
{
public:
	GLMeshRenderer(GLMesh& mesh, GLTransform& transform, GLMaterial& material);

	void init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program);
	void set_shader(std::shared_ptr<QOpenGLShaderProgram> shader_program);
	virtual void render(const GLCamera& camera, const std::map<light_sptr, obj_sptr>& lights) = 0;
	
	void render_wireframe(const GLCamera& camera);
	void upload_camera_details(const GLCamera& camera) const;
	void reload();

	virtual ~GLMeshRenderer() = default;
	
	std::shared_ptr<QOpenGLShaderProgram> shader_program_{ nullptr };
protected:
	
	QOpenGLBuffer vbo_;
	QOpenGLBuffer ibo_;
	QOpenGLVertexArrayObject vao_;
	
	GLMesh& mesh_;
	GLTransform& transform_;
	GLMaterial& material_;
	


	void enable_attributes() const;
	void disable_attributes() const;


private:

	void init_vbo();
	void init_ibo();
	void init_vao();
};

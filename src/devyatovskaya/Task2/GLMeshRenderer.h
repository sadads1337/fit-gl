#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <map>

#include "GLMesh.h"
#include "GLTransform.h"
#include "ShaderData.h"

class GLCamera;
class GLObject;
class QOpenGLFunctions_3_0;

using obj_sptr = std::shared_ptr<GLObject>;

class GLMeshRenderer
{
public:
    GLMeshRenderer(GLMesh& mesh, GLTransform& transform);

	void init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program);
	void set_shader(std::shared_ptr<QOpenGLShaderProgram> shader_program);
    virtual void render(QOpenGLFunctions_3_0& functions, const GLCamera& camera) = 0;
	
	void render_wireframe(QOpenGLFunctions_3_0& functions, const GLCamera& camera);
	void upload_camera_details(const GLCamera& camera) const;
	void reload();

	virtual ~GLMeshRenderer() = default;
	
	std::shared_ptr<QOpenGLShaderProgram> shader_program_;
protected:
	
	QOpenGLBuffer vbo_;
	QOpenGLBuffer ibo_;
	QOpenGLVertexArrayObject vao_;
	
	GLMesh& mesh_;
	GLTransform& transform_;

	void enable_attributes() const;
	void disable_attributes() const;


private:

	void init_vbo();
	void init_ibo();
	void init_vao();
};

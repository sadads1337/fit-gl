#include <utility>
#include "GLMeshRenderer.h"
#include "GLCamera.h"


void GLMeshRenderer::reload()
{
	init_vbo();
	init_ibo();
}

GLMeshRenderer::GLMeshRenderer(GLMesh& mesh, GLTransform& transform, GLMaterial& material)
	:	vbo_{ QOpenGLBuffer::VertexBuffer },
		ibo_{ QOpenGLBuffer::IndexBuffer },
		mesh_{ mesh },
		transform_{ transform },
		material_{ material }
{
}

void GLMeshRenderer::init_renderer(std::shared_ptr<QOpenGLShaderProgram> shader_program)
{
	initializeOpenGLFunctions();

	shader_program_ = std::move(shader_program);

	init_vao();
	init_vbo();
	init_ibo();

	enable_attributes();

	vao_.release();
}

void GLMeshRenderer::set_shader(std::shared_ptr<QOpenGLShaderProgram> shader_program)
{
	shader_program_ = std::move(shader_program);
}

void GLMeshRenderer::render_wireframe(const GLCamera& camera)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	shader_program_->bind();
	shader_program_->setUniformValue("wireframe_enabled", true);
	upload_camera_details(camera);
	
	vao_.bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_.indices.size()), GL_UNSIGNED_INT, nullptr);
	vao_.release();
}

void GLMeshRenderer::upload_camera_details(const GLCamera& camera) const
{
	shader_program_->setUniformValue("cameraPos", camera.position);
	shader_program_->setUniformValue("model", transform_.transform_);
	shader_program_->setUniformValue("normal_matrix", transform_.transform_.inverted().transposed());
	shader_program_->setUniformValue("view", camera.get_view_matrix());
	shader_program_->setUniformValue("projection", camera.get_projection_matrix());
}

void GLMeshRenderer::enable_attributes() const 
{
	shader_program_->enableAttributeArray("posAttr");
	shader_program_->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, sizeof(GLVertex));

	shader_program_->enableAttributeArray("normalAttr");
	shader_program_->setAttributeBuffer("normalAttr", GL_FLOAT, offsetof(GLVertex, normal), 3, sizeof(GLVertex));

	shader_program_->enableAttributeArray("colAttr");
	shader_program_->setAttributeBuffer("colAttr", GL_FLOAT, offsetof(GLVertex, color), 3, sizeof(GLVertex));

	shader_program_->enableAttributeArray("textureAttr");
	shader_program_->setAttributeBuffer("textureAttr", GL_FLOAT, offsetof(GLVertex, texture), 2, sizeof(GLVertex));
	
	shader_program_->enableAttributeArray("tangentAttr");
	shader_program_->setAttributeBuffer("aTangent", GL_FLOAT, offsetof(GLVertex, tangent), 3, sizeof(GLVertex));
	
	shader_program_->enableAttributeArray("bitangentAttr");
	shader_program_->setAttributeBuffer("aBitangent", GL_FLOAT, offsetof(GLVertex, bitangent), 3, sizeof(GLVertex));
}

void GLMeshRenderer::disable_attributes() const
{
	shader_program_->disableAttributeArray("posAttr");
	shader_program_->disableAttributeArray("normalAttr");
	shader_program_->disableAttributeArray("textureAttr");
	shader_program_->disableAttributeArray("colAttr");
	shader_program_->disableAttributeArray("tangentAttr");
	shader_program_->disableAttributeArray("bitangentAttr");
}


void GLMeshRenderer::init_vbo()
{
	vbo_.create();
	if(vbo_.isCreated()) {
		vbo_.bind();
	} else {
		qWarning("Could not bind vertex buffer to the context");
		return;
	}

	vbo_.allocate(mesh_.vertices.data(), static_cast<int>(mesh_.vertices.size() * sizeof(GLVertex)));
}

void GLMeshRenderer::init_ibo()
{
	ibo_.create();
	if (ibo_.isCreated()) {
		ibo_.bind();
	}
	else {
		qWarning("Could not bind index buffer to the context");
		return;
	}

	ibo_.allocate(mesh_.indices.data(), static_cast<int>(mesh_.indices.size() * sizeof(unsigned)));
}

void GLMeshRenderer::init_vao()
{
	vao_.create();
	if (vao_.isCreated()) {
		vao_.bind();
	}
	else {
		qWarning("Could not bind vertex array buffer to the context");
	}
	
}



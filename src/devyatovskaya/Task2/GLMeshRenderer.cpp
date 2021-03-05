#pragma warning(disable : 4267)
#include <utility>
#include "GLMeshRenderer.h"

void GLMeshRenderer::init_shaders(const std::string& vertex, const std::string& fragment)
{
    shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex.c_str());
    shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment, fragment.c_str());
    shader_program_.link();
}


GLMeshRenderer::GLMeshRenderer()
	:	vertex_buf_{ QOpenGLBuffer::VertexBuffer },
		index_buf_{ QOpenGLBuffer::IndexBuffer }	
{
	
}

void GLMeshRenderer::init_renderer(GLMesh* mesh, const std::string& vertex, const std::string& fragment)
{
	initializeOpenGLFunctions();

	mesh_ = mesh;
    init_shaders(vertex, fragment);

	init_vbo();
	init_ibo();
}

void GLMeshRenderer::enable_attributes()
{
    shader_program_.enableAttributeArray("posAttr");
    shader_program_.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, sizeof(GLVertex));

    shader_program_.enableAttributeArray("colAttr");
    shader_program_.setAttributeBuffer("colAttr", GL_FLOAT, offsetof(GLVertex, color), 3, sizeof(GLVertex));
}

void GLMeshRenderer::disable_attributes()
{
    shader_program_.disableAttributeArray("posAttr");
    shader_program_.disableAttributeArray("colAttr");
}

void GLMeshRenderer::init_vbo()
{
	vertex_buf_.create();
	vertex_buf_.bind();

	vertex_buf_.allocate(mesh_->vertices.data(), mesh_->vertices.size() * sizeof(GLVertex));
}

void GLMeshRenderer::init_ibo()
{
	index_buf_.create();
	index_buf_.bind();


	index_buf_.allocate(mesh_->indices.data(),mesh_->indices.size() * sizeof(unsigned));
}

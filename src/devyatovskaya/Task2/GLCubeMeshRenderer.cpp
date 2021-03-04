#include "GLCubeMeshRenderer.h"

void GLCubeMeshRenderer::render()
{
	shader_program_.bind();
	
	vertex_buf_.bind();
	index_buf_.bind();

	enable_attributes();

	draw_faces();
	draw_edges();
	
	disable_attributes();
	
	vertex_buf_.release();
	index_buf_.release();
	
}

void GLCubeMeshRenderer::draw_edges()
{
	shader_program_.setUniformValue("wireframe", true);
	
	glDisable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_->indices.size()), GL_UNSIGNED_INT, nullptr);
}

void GLCubeMeshRenderer::draw_faces()
{
	shader_program_.setUniformValue("wireframe", false);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.5, 1.);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_->indices.size()), GL_UNSIGNED_INT, nullptr);
}

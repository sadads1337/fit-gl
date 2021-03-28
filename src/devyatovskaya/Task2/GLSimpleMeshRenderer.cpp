#include <QOpenGLFunctions_3_0>

#include "GLSimpleMeshRenderer.h"

GLSimpleMeshRenderer::GLSimpleMeshRenderer(GLMesh& mesh, GLTransform& transforml)
	: GLMeshRenderer{ mesh, transform, material }
{
	
}



void GLSimpleMeshRenderer::render(QOpenGLFunctions_3_0& functions, const GLCamera& camera, const std::map<light_sptr, obj_sptr>& lights)
{
	functions.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader_program_->bind();
	shader_program_->setUniformValue("wireframe_enabled", false);
	upload_camera_details(camera);

	if (!material_.is_light_source) {
		upload_lights_details(lights);
		material_.upload_to_shader(shader_program_);
	}
	
	upload_texture_details(functions);
	
	vao_.bind();
	functions.glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_.indices.size()), GL_UNSIGNED_INT, nullptr);
	vao_.release();
	
	if(!material_.texture.empty()) {
		material_.texture.front().texture_data->release();
	}
	if (!material_.normals.empty()) {
		material_.normals.front().texture_data->release();
	}
	
}

void GLSimpleMeshRenderer::upload_lights_details(const std::map<light_sptr, obj_sptr>& lights) const
{
	auto point_lights = 0u;
	auto spot_lights = 0u;
	auto directed_lights = 0u;
	for (const auto& [light, light_object] : lights) {

		auto id = 0u;
		if (std::dynamic_pointer_cast<GLPointLight>(light) != nullptr)
		{
			id = point_lights++;
		}
		if (std::dynamic_pointer_cast<GLDirectedLight>(light) != nullptr)
		{
			id = directed_lights++;
		}
		if (std::dynamic_pointer_cast<GLSpotLight>(light) != nullptr)
		{
			id = spot_lights++;
		}
		light->upload_to_shader(shader_program_, id);

	}

	shader_program_->setUniformValue("directed_lightsCount", static_cast<int>(directed_lights));
	shader_program_->setUniformValue("point_lightsCount", static_cast<int>(point_lights));
	shader_program_->setUniformValue("spot_lightsCount", static_cast<int>(spot_lights));
}

void GLSimpleMeshRenderer::upload_texture_details(QOpenGLFunctions_3_0& functions)
{
	if (!material_.texture.empty()) {
		shader_program_->setUniformValue("ourTexture", 0);
		functions.glActiveTexture(GL_TEXTURE0);
		material_.texture.front().texture_data->bind();
	}

	if (!material_.normals.empty()) {
		shader_program_->setUniformValue("normalMap", 1);
		functions.glActiveTexture(GL_TEXTURE1);
		material_.normals.front().texture_data->bind();
	}
}

#include "GLSimpleMeshRenderer.h"
#include "GLPointLight.h"
#include "GLDirectedLight.h"
#include "GLSpotLight.h"
#include "GLMaterial.h"

void GLSimpleMeshRenderer::render(const GLCamera& camera, const std::map<light_sptr, obj_sptr>& lights)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader_program_->bind();
	shader_program_->setUniformValue("wireframe_enabled", false);
	upload_camera_details(camera);

	if (!material_.is_light_source) {
		upload_lights_details(lights);
		material_.upload_to_shader(shader_program_);
	}
	
	glActiveTexture(GL_TEXTURE0);
	material_.texture.texture_data->bind();
	// glActiveTexture(GL_TEXTURE1);
	// material_.texture.normal_map_data->bind();
	
	vao_.bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_.indices.size()), GL_UNSIGNED_INT, nullptr);
	vao_.release();
	
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
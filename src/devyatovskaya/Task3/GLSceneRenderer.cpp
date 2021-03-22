#include "GLSceneRenderer.h"
#include "GLScene.h"

GLSceneRenderer::GLSceneRenderer()
	:	mode_ { gl_fill | gl_cull_face_back }
{
}

void GLSceneRenderer::init()
{
	initializeOpenGLFunctions();
}

void GLSceneRenderer::render(GLScene& scene)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mode_ & gl_cull_face_back) {
		glCullFace(GL_BACK);
	}

	if (mode_ & gl_cull_face_front) {
		glCullFace(GL_FRONT);
	}

	
	render_lights_objects(scene);
	std::for_each(scene.objects.begin(), scene.objects.end(), [&](std::shared_ptr<GLObject>& object)
		{
			if(mode_ & gl_fill) {
				object->renderer->render(scene.camera_mover.camera, scene.lights_objects);
			}


			if (mode_ & gl_line) {
				glEnable(GL_POLYGON_OFFSET_LINE);
				glPolygonOffset(-1, -1);

				object->renderer->render_wireframe(scene.camera_mover.camera);

				glDisable(GL_POLYGON_OFFSET_LINE);
			}
		});
}

void GLSceneRenderer::set_mode(const uint8_t mode)
{
	mode_ |= mode;
}

void GLSceneRenderer::reset_mode(const uint8_t mode)
{
	mode_ &= ~mode;
}

void GLSceneRenderer::render_lights_objects(GLScene& scene) const
{
	for (auto& [light, light_object] : scene.lights_objects)
	{
		light_object->renderer->render(scene.camera_mover.camera, scene.lights_objects);
	}
}

#include "GLSceneRenderer.h"
#include "GLScene.h"

GLSceneRenderer::GLSceneRenderer() : mode_{gl_fill | gl_cull_face_back} {}

void GLSceneRenderer::init(const int width, const int height,
                           const int retina_scale) {
  functions_.initializeOpenGLFunctions();

  functions_.glClearColor(0.1f, 0.5f, 2.f, 1);
  functions_.glViewport(0, 0, width * retina_scale, height * retina_scale);
  functions_.glEnable(GL_DEPTH_TEST);
  functions_.glEnable(GL_CULL_FACE);
}

void GLSceneRenderer::render(GLScene &scene) {
  functions_.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  functions_.glEnable(GL_BLEND);
  functions_.glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (mode_ & gl_cull_face_back) {
    functions_.glCullFace(GL_BACK);
  }

  if (mode_ & gl_cull_face_front) {
    functions_.glCullFace(GL_FRONT);
  }

  render_lights_objects(scene);
  std::for_each(scene.objects.begin(), scene.objects.end(),
                [&](std::shared_ptr<GLObject> &object) {
                  if (mode_ & gl_fill) {
                    object->renderer->render(functions_,
                                             scene.camera_mover.camera,
                                             scene.lights_objects);
                  }

                  if (mode_ & gl_line) {
                    functions_.glEnable(GL_POLYGON_OFFSET_LINE);
                    functions_.glPolygonOffset(-1, -1);

                    object->renderer->render_wireframe(
                        functions_, scene.camera_mover.camera);

                    functions_.glDisable(GL_POLYGON_OFFSET_LINE);
                  }
                });
}

void GLSceneRenderer::set_mode(const uint8_t mode) { mode_ |= mode; }

void GLSceneRenderer::reset_mode(const uint8_t mode) { mode_ &= ~mode; }

void GLSceneRenderer::render_lights_objects(GLScene &scene) {
  for (auto &[light, light_object] : scene.lights_objects) {
    light_object->renderer->render(functions_, scene.camera_mover.camera,
                                   scene.lights_objects);
  }
}

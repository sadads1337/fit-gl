#include "GLObject.h"

void GLObject::init_renderer(
    std::shared_ptr<QOpenGLShaderProgram> shader_program) const {
  renderer->init_renderer(std::move(shader_program));
}

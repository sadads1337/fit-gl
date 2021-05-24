#include "ShaderData.h"

std::shared_ptr<QOpenGLShaderProgram> ShaderData::get_shader_program() {
  if (shader_program == nullptr) {
    shader_program = std::make_shared<QOpenGLShaderProgram>();
    shader_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                            vertex.c_str());
    shader_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                            fragment.c_str());
    shader_program->link();
  }
  return shader_program;
}

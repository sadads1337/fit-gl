#include "cubeedges.h"

void CubeEdges::DrawGeometry(QOpenGLShaderProgram *program) {
  if (need_init_) {
    initializeOpenGLFunctions();
    need_init_ = false;
  }

  const auto vertex_location = program->attributeLocation("posAttr");
  Q_ASSERT(vertex_location != -1);
  const auto color_location = program->attributeLocation("colAttr");
  Q_ASSERT(color_location != -1);

  glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0,
                        vertex_buf_.data());
  glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 0,
                        color_buf_.data());

  glEnableVertexAttribArray(vertex_location);
  glEnableVertexAttribArray(color_location);

  for (auto i = 0; i <= 12; i += 4) {
    glDrawArrays(GL_LINE_LOOP, i, 4);
  }

  glDisableVertexAttribArray(vertex_location);
  glDisableVertexAttribArray(color_location);
}

void CubeEdges::InitGeometry() {
  setVertices();
  setColor();
}

void CubeEdges::setVertices() {
  GLfloat a = edge_len_ / 2;
  unsigned dim = 3;

  for (unsigned i = 0; i < 8 * dim; i += dim) {
    auto idx = static_cast<int>(i / dim);
    vertex_buf_[i] = idx % 7 == 0 || (idx > 2 && idx < 5) ? -a : a;
    vertex_buf_[i + 1] = idx > 1 && idx < 6 ? -a : a;
    vertex_buf_[i + 2] = idx > 3 ? -a : a;
  }

  for (unsigned i = 8 * dim; i < 16 * dim; i += dim) {
    auto idx = static_cast<int>(i / dim) - 8;
    vertex_buf_[i] = idx > 3 ? a : -a;
    vertex_buf_[i + 1] = idx > 1 && idx < 6 ? -a : a;
    vertex_buf_[i + 2] = (idx > 0 && idx < 3) || (idx > 4 && idx < 7) ? -a : a;
  }
}

void CubeEdges::setColor() {
  std::fill(color_buf_.begin(), color_buf_.end(), 0);
}

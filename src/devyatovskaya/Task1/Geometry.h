#pragma once
#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <memory>
#include <vector>

class Geometry : protected QOpenGLFunctions_3_1 {
public:
  Geometry() = delete;
  explicit Geometry(const GLuint vertex_count) : vertex_count_{vertex_count} {}

  virtual void DrawGeometry(QOpenGLShaderProgram *program) = 0;
  virtual void InitGeometry() = 0;

  std::vector<GLfloat> &ColorArray();
  const std::vector<GLfloat> &ColorArray() const;

  std::size_t VertexCount() const;

protected:
  bool need_init_{true};
  GLuint vertex_count_;

  std::vector<GLfloat> vertex_buf_{};
  std::vector<GLfloat> color_buf_{};

  std::vector<GLsizei> index_buf_{};

  virtual void setVertices() = 0;
  virtual void setColor() = 0;
};

using geometry_uptr = std::unique_ptr<Geometry>;

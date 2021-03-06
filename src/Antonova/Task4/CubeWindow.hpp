#pragma once

#include <Base/GLWindow.hpp>
#include <QBasicTimer>
#include <QColorDialog>
#include <QMouseEvent>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

namespace fgl {

struct VertexData {
  QVector3D position;
  QVector3D normal;
  QVector2D texture_coord;
  QVector3D tangent;
};

class CubeWindow final : public GLWindow {
public:
  void init() override;
  void render() override;

  void makeCube(const float side_size, const int n_points);
  void initTexture();

  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void timerEvent(QTimerEvent *e) override;

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint normAttr_ = 0;
  GLint textureAttr_ = 0;
  GLint tangentAttr_ = 0;

  GLint colorUniform_ = 0;
  GLint morphUniform_ = 0;
  GLint lightPosUniform_ = 0;
  GLint viewPosUniform_ = 0;
  GLint lightColorUniform_ = 0;
  GLint textureUniform_ = 0;
  GLint normalMapUniform_ = 0;

  // matrices:
  GLint model_matrixUniform_ = 0;
  GLint view_matrixUniform_ = 0;
  GLint projection_matrixUniform_ = 0;

  QOpenGLBuffer vertexBuffer;
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};

  QVector3D cubeColor{1.0f, 0.8f, 0.9f};
  int cubes_grid_size = 1;
  float cube_side_size = 5.0;

  QVector2D mousePressPosition;
  QVector3D rotationAxis{0.0f, 1.0f, 0.0f};
  QBasicTimer timer;

  float morph_parameter = 0.0f;
  int morph_direction = 1;

  QVector3D lightColor{1.0f, 1.0f, 1.0f};
  QVector3D lightPosition{1.0f, 1.0f, 1.0f};
  QVector3D viewPosition{0.0f, 0.0f, 0.0f};

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // texture
  std::shared_ptr<QOpenGLTexture> texture = nullptr;
  std::shared_ptr<QOpenGLTexture> normalMap = nullptr;


    // Frame counter for animation.
  int frame_ = 0;
};

} // namespace fgl
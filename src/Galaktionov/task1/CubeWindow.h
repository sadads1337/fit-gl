#pragma once

#include <Base/GLWindow.hpp>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <memory>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>
#include <array>
#include <QWindow>

struct Vertex_Data {
    Vertex_Data()
    {
    }
    Vertex_Data(QVector3D pos, QVector2D tex, QVector3D norm):
        position(pos), texture_coordinates(tex), normal(norm)
    {
    }

    QVector3D position;
    QVector2D texture_coordinates;
    QVector3D normal;
};

class CubeWindow final : public fgl::GLWindow {

public:
  CubeWindow(QWindow *parent = 0);
  ~CubeWindow() override;

  void init() override;
  void render() override;

protected:
  void Init_Shaders();
  void Init_Cube(float x, float y, float z, float width);

  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  QMatrix4x4 m_projection_matrix;
  QOpenGLShaderProgram m_shader_program;
  QOpenGLTexture *m_shader_texture;

  QOpenGLBuffer m_vertex_buffer;
  QOpenGLBuffer m_index_buffer;
  int frame_ = 0;

  GLint vertex_location;
  GLint texture_location;
  GLint matrixUniform_;

  QVector4D changeColor{1.0, 1.0, 0.0, 1};
  QVector2D mousePressPosition{0.0, 0.0};
  QVector3D rotationAxis{0.0, 1.0, 0.0};
};

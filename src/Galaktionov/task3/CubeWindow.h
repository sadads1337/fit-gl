#pragma once

#include <Base/GLWindow.hpp>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <memory>
#include <QMouseEvent>
#include <QScreen>
#include <array>
#include <QString>

struct Vertex_Data {
    QVector3D position;
    QVector3D norm;
};

class CubeWindow final : public fgl::GLWindow {

public:
  void init() override;
  void render() override;

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  QOpenGLShaderProgram m_shader_program;

  QOpenGLBuffer m_vertex_buffer;
  QOpenGLBuffer m_index_buffer{QOpenGLBuffer::Type::IndexBuffer};
  int frame_ = 0;

  GLint vertex_location;
  GLint normal;
  GLint matrixUniform_;

  QVector4D changeColor{1.0f, 1.0f, 0.0f, 1};
  QVector2D mousePressPosition_{0., 0.};
  QVector3D rotationAxis{0.0f, 1.0f, 0.0f};
};

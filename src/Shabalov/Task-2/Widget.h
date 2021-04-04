#pragma once

#include "Object3D.h"
#include <QBasicTimer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QTimerEvent>
#include <QWheelEvent>
#include <memory>

class Widget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;
  void setXRotation(float angle);
  void setYRotation(float angle);
  void setZRotation(float angle);
  void setT(float value);
  void setColor(const QColor &color);

protected:
  void initializeGL() override;
  void resizeGL(const int w, const int h) override;
  void paintGL() override;
  void initShaders();
  void initCube(const float width, const int N);

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void timerEvent(QTimerEvent *event) override;

private:
  QMatrix4x4 m_projectionMatrix;
  QOpenGLShaderProgram m_program;
  QVector2D m_mousePosition;
  QQuaternion m_rotation;

  float x_rot;
  float y_rot;
  float z_rot;
  float m_z;
  float m_t;
  float angleObject;
  QVector<std::shared_ptr<Object3D>> m_objects;
  QColor m_color;
  QBasicTimer m_timer;
};

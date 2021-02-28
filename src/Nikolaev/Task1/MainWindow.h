#pragma once

#include "Controller/InputController.h"
#include "GeometryEngine.h"

#include <QBasicTimer>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QVector2D>

class GeometryEngine;

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  using QOpenGLWidget::QOpenGLWidget;

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void timerEvent(QTimerEvent *e) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void initShaders();

private:
  std::unique_ptr<InputController> m_change_colors;

  QBasicTimer timer;
  QOpenGLShaderProgram program;
  std::unique_ptr<GeometryEngine> geometries = nullptr;

  QMatrix4x4 projection;

  QVector2D mousePressPosition;
  QVector3D rotationAxis;
  qreal angularSpeed = 0;
  QQuaternion rotation;

  int frame_ = 0;
};
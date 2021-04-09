#pragma once
#ifndef COUBSARMYWIDGET_H
#define COUBSARMYWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QLabel>
#include <QTime>
#include <QOpenGLTexture>
#include "coub.h"
#include "objectmodel.h"
#include "normals.h"
#include "object.h"
#include "sourcelight.h"
#include "colorowner.h"
#include "sphere.h"

class CoubsArmy : public QOpenGLWidget, protected QOpenGLFunctions
{
public:

  void initializeGL() override;
  void initMatrix();
  void initProgram();
  void initVaoVbo();
  void initShadersParam();
  void initObject();
  void initTextures();

  void paintGL() override;

  void setSphere(float x, float y);

  void setRotation(std::vector<GLfloat> rt);
  void setColor(QColorDialog* cd , int active);
  void setFactor(float nf);
  void setRotate(bool fl);
  void setLightCoefs(std::vector<int> vec);
  void setActivateLight(std::vector<bool>vec);

  void setDirectionLightPosition(QVector4D pos);
  void setPointLightPosition(QVector4D pos);

  CoubsArmy(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()):QOpenGLWidget(parent,f), timer(new QTimer(this)){}

  ~CoubsArmy(){}

private:
  QOpenGLBuffer *m_vbo = nullptr;
  QOpenGLVertexArrayObject *m_vao = nullptr;

  Object object;

  SourceLight directionLight;
  SourceLight ambientLight;
  SourceLight pointLight;

  std::unique_ptr<QOpenGLTexture> texture, normalMap;

  std::vector<ObjectModel> matrix;

  LightFactors coefs;

  ColorOwner colorOwner;

  QColor color;
  QColorDialog* colorDialog = nullptr;

  GLint m_norAttr = 0;
  GLint m_posAttr = 0;

  GLint m_trMatrix =0;
  GLint m_matrixUniform = 0;

  QOpenGLFunctions *f = nullptr;
  QOpenGLShaderProgram *m_program = nullptr;
  int m_frame = 0;
  QTimer* timer = nullptr;
};

#endif // COUBSARMYWIDGET_H

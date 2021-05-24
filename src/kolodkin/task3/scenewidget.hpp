#pragma once

#define _ISC_ inline static constexpr

#include "cameraview.hpp"
#include "direcltylight.hpp"
#include "keyboard.hpp"
#include "materialfactory.hpp"
#include "meshfactory.hpp"
#include "objectsgrid.hpp"
#include "pointlightsource.hpp"
#include "scene.hpp"
#include "sceneobject.hpp"

#include <QBasicTimer>
#include <QColorDialog>
#include <QElapsedTimer>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <unordered_map>
#include <vector>

template <class T> using sPtr = std::shared_ptr<T>;

class SceneWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  SceneWidget() = delete;
  SceneWidget(QWidget *parent = nullptr);
  ~SceneWidget();

signals:
  void MaterialShininess(float);
  void newMaterial(QString const &);
  void fpsChanged(int);

public slots:
  void selectCamera();
  void selectPointLight();

  void setGridSteps(int steps);
  void setGridStepLen(float length);

  void setMaterialAmbient(float val);
  void setMaterialDiffuse(float val);
  void setMaterialSpecular(float val);
  void setMaterialShininess(float val);

  void setDirDirection(QVector3D dir);
  void setDirInt(float intensity);
  void setDirColor(QColor const &color);

  void setPointConst(float constant);
  void setPointLin(float linear);
  void setPointQuad(float quadric);
  void setPointInt(float intensity);
  void setPointColor(QColor const &color);

  void setSpotConst(float constant);
  void setSpotLin(float linear);
  void setSpotQuad(float quadric);
  void setSpotInt(float intensity);
  void setSpotColor(QColor const &color);
  void setCutOff(float cutOff);
  void setOuterCutOff(float outerCutOff);

  void setObjectMaterial(int index);

private:
  void cleanup();

  void mousePressEvent(QMouseEvent *e) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void wheelEvent(QWheelEvent *ev) override;
  void timerEvent(QTimerEvent *e) override;
  QSize minimumSizeHint() const override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void moveProcess();
  void initShaders();
  void setBackGroundColor();

  _ISC_ int initSteps = 8;
  _ISC_ float initFov = 60.f;
  _ISC_ float zNear = 0.1;
  _ISC_ float zFar = 100.;
  _ISC_ std::size_t maxKeyCode = 0xff;
  _ISC_ unsigned deltaTimeMsec = 12;

  _ISC_ QVector3D forward{0.f, 0.f, 1.f};
  _ISC_ QVector3D upward{0.f, 1.f, 0.f};
  _ISC_ QVector3D rightward{1.f, 0.f, 0.f};
  _ISC_ QVector3D backward = -forward;
  _ISC_ QVector3D leftward = -rightward;
  _ISC_ QVector3D downward = -upward;
  _ISC_ size_t GridSteps = 50;
  _ISC_ float GridStepLength = 1.5f;
  _ISC_ float DirLightIntensity = 0.1;
  _ISC_ QVector3D DirLightDirection{0, -1, 0};

  Keyboard keyboard{Qt::Key_W,     Qt::Key_A,     Qt::Key_S,
                    Qt::Key_D,     Qt::Key_Z,     Qt::Key_Space,
                    Qt::Key_Up,    Qt::Key_Down,  Qt::Key_Left,
                    Qt::Key_Right, Qt::Key_Slash, Qt::Key_Greater};

  Material baseMaterial = MaterialFactory::Gold;
  sPtr<Material> pMaterial = std::make_shared<Material>(baseMaterial);
  float ambientFac = 1.f;
  float diffuseFac = 1.f;
  float specularFac = 1.f;

  sPtr<DirecltyLight> pDirLight{};
  sPtr<ObjectsGrid> pObjectsGrid{};

  sPtr<PointLightSource> pPointLight{};

  float fov = initFov;
  sPtr<SpotLightSource> pSpotLight{};

  sPtr<QOpenGLShaderProgram> pObjectShader =
      std::make_shared<QOpenGLShaderProgram>();
  sPtr<QOpenGLShaderProgram> pLightShader =
      std::make_shared<QOpenGLShaderProgram>();

  Scene scene;
  sPtr<CameraView> pCamera = std::make_shared<CameraView>(
      QVector3D{0.f, 1.2f, 0.f}, QVector3D{1.f, 0.f, 1.f});

  sPtr<Object> pDrivenObject = std::static_pointer_cast<Object>(pCamera);

  float cameraSpeed = 3.0;

  QVector2D mouseLastPosition;
  std::vector<bool> keyStates;

  int framesCount = 0;
  float deltaTime = 0.f;
  QElapsedTimer fpsTimer;
  QElapsedTimer deltaTimer;

  QBasicTimer timer;
};

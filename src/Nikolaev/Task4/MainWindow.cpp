#include "MainWindow.h"
#include <QScreen>
#include <string>

void MainWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference
  // vector
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  // Accelerate angular speed relative to the length of the mouse sweep
  qreal acc = diff.length() / 100.0;

  // Calculate new rotation axis as weighted sum
  rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

  // Increase angular speed
  angularSpeed += acc;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  inputCtrl->keyPressEvent(event);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    m_z += 0.25;
  } else if (event->angleDelta().y() < 0) {
    m_z -= 0.25;
  }
  update();
}

void MainWindow::timerEvent(QTimerEvent *) {
  // Decrease angular speed (friction)
  angularSpeed *= 0.99;

  // Stop rotation when speed goes below threshold
  if (angularSpeed < 0.01) {
    angularSpeed = 0.0;
  } else {
    // Update rotation
    rotation =
        QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
  }
  update();
}

void MainWindow::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(0.1f, 0.1f, 0.1f, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  initCubeTextures(0);
  initShaders(InputController::Phong);

  m_z = -3.0f;
  inputCtrl = std::make_unique<InputController>();

  m_objects.append(std::make_shared<GeometryEngine>());
  m_objects[m_objects.size() - 1]->translate(QVector3D(0, 0, 0));

  // Use QBasicTimer because its faster than QTimer
  timer.start(12, this);
}

void MainWindow::initCubeTextures(unsigned int currentTexture) {
  auto textureFileName =
      (":/Textures/texture" + std::to_string(currentTexture) + ".png");
  auto ctextureFileName = textureFileName.c_str();

  m_texture =
      std::make_unique<QOpenGLTexture>((QImage(ctextureFileName).mirrored()));
  m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
  m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::Repeat);

  m_normMap =
      std::make_unique<QOpenGLTexture>((QImage(ctextureFileName).mirrored()));
  m_normMap->setMinificationFilter(QOpenGLTexture::Nearest);
  m_normMap->setMagnificationFilter(QOpenGLTexture::Linear);
  m_normMap->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWindow::initShaders(unsigned int currentShader) {
  program.removeAllShaders();

  /* Init Phong shader */
  if (currentShader == InputController::Phong) {
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/Shaders/phong_vshader.glsl"))
      close();

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/Shaders/phong_fshader.glsl"))
      close();
  }
  /* Init Gouraud shader */
  else if (currentShader == InputController::Gouraud) {
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/Shaders/gouraud_vshader.glsl"))
      close();

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/Shaders/gouraud_fshader.glsl"))
      close();
  }

  // Link shader pipeline
  if (!program.link())
    close();

  // Bind shader pipeline for use
  if (!program.bind())
    close();
}

void MainWindow::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const qreal zNear = 2.0, zFar = 15.0, fov = 60.0;

  // Reset projection
  projection.setToIdentity();

  // Set perspective projection
  projection.perspective(fov, aspect, zNear, zFar);
}

void MainWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (inputCtrl->swapKeyFlag) {
    initCubeTextures(inputCtrl->currentTexture);

    for (auto &m_object : m_objects) {
      m_object->initCubeGeometry(1.0f, inputCtrl->vertexFactor);
    }
    initShaders(inputCtrl->currentShader);
    inputCtrl->swapKeyFlag = false;
  }

  program.bind();

  // Calculate model view transformation
  QMatrix4x4 matrixView;
  matrixView.translate(0.0f, 0.0f, m_z);
  matrixView.rotate(rotation);

  program.setUniformValue("projection_matrix", projection);
  program.setUniformValue("view_matrix", matrixView);
  program.setUniformValue("t", static_cast<GLfloat>(frame_));

  program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
  program.setUniformValue("u_lightPower", 1.0f);

  m_texture->bind(0);
  program.setUniformValue("u_texture", 0);
  m_normMap->bind(0);
  program.setUniformValue("u_normMap", 0);

  // Draw cubes
  for (auto &m_object : m_objects) {
    m_object->drawCubeGeometry(&program, context()->functions());
  }

  program.release();

  ++frame_;
}
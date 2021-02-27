#pragma once

#include "cubeedges.h"
#include "cubegeometry.h"
#include "cubepainter.h"
#include <Base/GLWindow.hpp>
#include <QColorDialog>
#include <QSlider>

#include <memory>

#include <QOpenGLShaderProgram>

namespace fgl {

class CubeWindow : public GLWindow {
public:
  explicit CubeWindow(QWindow *parent = nullptr) : GLWindow{parent} {
    cube_geometry_.InitGeometry();
    edges_geometry_.InitGeometry();
  }
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;

  void init() override;
  void render() override;

private:
  QColorDialog color_dialog_;
  QMatrix4x4 projection_{};

  QSlider slider_x_;
  QSlider slider_y_;
  QSlider slider_z_;

  CubeGeometry cube_geometry_{1.0f};
  CubeEdges edges_geometry_{1.0f};
  CubePainter painter_{cube_geometry_};

  QVector2D mouse_press_position_;
  QVector3D rotation_axis_;
  qreal angular_speed_ = 0;
  QQuaternion rotation_;

  void setRotation();
  void initColorDialog();
  void initSlidersDialog();
  void resizeGL();

  QOpenGLShaderProgram program_{this};
  int frame_ = 0;
};

} // namespace fgl

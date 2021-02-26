#pragma once
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSlider>
#include "cubeedges.h"
#include "cubegeometry.h"
#include "cubepainter.h"
#include <memory>
#include <QOpenGLShaderProgram>

class CubeWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    CubeWindow(QWidget* parent = nullptr)
        : QOpenGLWidget {parent}{
        cube_geometry_.InitGeometry();
        inner_edges_geometry_.InitGeometry();
        outer_edges_geometry_.InitGeometry();
    };

protected:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;

    void initializeGL() override;
    void paintGL() override;

public slots:
    void get_color(const QColor& color);

private:
  QColor color_{255, 255, 255 };

      std::vector<std::unique_ptr<Geometry>> geometries_{};

      QOpenGLShaderProgram program_{ this };

      CubeGeometry cube_geometry_{ 0.5f };
      CubeEdges outer_edges_geometry_{ 1.0f };
      CubeEdges inner_edges_geometry_{ 0.5f };

      CubePainter painter_{ cube_geometry_ };


      QVector2D mouse_press_position_;
      QVector3D rotation_axis_;
      qreal angular_speed_ = 0;
      QQuaternion rotation_;


      void setRotation();
};

#pragma once
#include <QBasicTimer>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "FPSCounter.h"
#include "GLSceneRenderer.h"
#include "LightingDialog.h"
#include "MorphingDialog.h"
#include "PreparedScenes.h"
#include "RenderDialog.h"

class PhongLightingWidget final : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit PhongLightingWidget(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

public slots:
  void show_render_dialog();

  void show_shininess_dialog();
  void show_light_color_dialog();
  void show_ambient_color_dialog();
  void show_diffuse_color_dialog();
  void show_specular_color_dialog();
  void show_morphing_widget();

  void set_render_mode(int state);
  void catch_fps(const QString &);

  void set_light_color(const QColor &color);
  void set_ambient_color(const QColor &color);
  void set_diffuse_color(const QColor &color);
  void set_specular_color(const QColor &color);

  void set_shininess(int shininess);
  void set_morph_factor(int morph_factor);

signals:
  void send_fps(const QString &);

protected:
  void initializeGL() override;
  void paintGL() override;

  void timerEvent(QTimerEvent *) override;
  void update_framerate();

public:
  PreparedScenes prep_scenes_;

  std::size_t scene_count_{0};
  bool is_morphing_{false};
  float morph_factor_{0.0};

  GLScene current_scene_;
  GLSceneRenderer renderer_;

  RenderDialog render_dialog_;

  LightingDialog lighting_dialog_;
  MorphingDialog morphing_dialog_;
  QColorDialog light_color_dialog_;
  QColorDialog ambient_color_dialog_;
  QColorDialog diffuse_color_dialog_;
  QColorDialog specular_color_dialog_;

  FPSCounter fps_counter_;
  QBasicTimer timer_;
};

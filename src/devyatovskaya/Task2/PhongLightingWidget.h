#pragma once
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColorDialog>
#include <QBasicTimer>

#include "RenderDialog.h"
#include "PreparedScenes.h"
#include "GLSceneRenderer.h"
#include "MorphingDialog.h"


class PhongLightingWidget final : public QOpenGLWidget
{
	Q_OBJECT
public:
	explicit PhongLightingWidget(QWidget* parent = nullptr);
	
	void keyPressEvent(QKeyEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

public slots:
	void show_render_dialog();

	void show_morphing_widget();
	
	void set_render_mode(int state);
	
	void set_morph_factor(int morph_factor);
	
protected:
	void initializeGL() override;
	void paintGL() override;

	void timerEvent(QTimerEvent*) override;
	void update_framerate();
	
public:
	PreparedScenes prep_scenes_;
	
	std::size_t scene_count_{ 0 };
	bool is_morphing_{ false };
	float morph_factor_{ 0.0 };

	
	GLScene current_scene_;
	GLSceneRenderer renderer_;

	RenderDialog render_dialog_;

	QBasicTimer timer_;
};

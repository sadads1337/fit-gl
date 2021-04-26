#pragma once
#include <limits>
#include "GLCamera.h"

enum class CameraMovement {
	FORWARD = Qt::Key_W,
	BACKWARD = Qt::Key_S,
	LEFT = Qt::Key_A,
	RIGHT = Qt::Key_D,
	UP = Qt::Key_Space,
	DOWN = Qt::Key_Shift,

	ROTATE_RIGHT = Qt::Key_Q,
	ROTATE_LEFT = Qt::Key_E
};


class GLCameraMover final
{
public:
	void move();
	bool activated{ false };
	GLCamera camera{ { 0, 0, 3 } };

	void set_camera_speed(float delta_time);
	void set_mouse_pos(const QPointF& pos);
	void update_camera_zoom(float dy);
	void set_key(int key);
	void reset_key(int key);

	
private:

	int last_pressed_key_{ std::numeric_limits<int>::max() };
	float initial_camera_speed_{ 10.5f };
	float current_camera_speed_{ initial_camera_speed_ };

	QPointF last_mouse_pos_{};
	bool first_mouse_callback_{ true };
	
	std::map<CameraMovement, QVector3D> controls_ = 
	{
			{CameraMovement::FORWARD,	{0,0,1}	},
			{CameraMovement::BACKWARD,	{0,0,-1}	},
			{CameraMovement::LEFT,		{-1,0,0}	},
			{CameraMovement::RIGHT,		{1,0,0}	},
			{CameraMovement::UP,		{0,1,0}	},
			{CameraMovement::DOWN,		{0,-1,0}	}
	};

	void update_camera_pos(float dx, float dy);
	void update_camera_direction(const QPointF& pos);
};
#include "GLCameraMover.h"



void GLCameraMover::move()
{
	const auto& direction = controls_[static_cast<CameraMovement>(last_pressed_key_)];
	if(direction == QVector3D{0, 0, 0}) {
		return;
	}
	
	camera.translate(direction * current_camera_speed_);
}

void GLCameraMover::set_camera_speed(const float delta_time)
{
	current_camera_speed_ = initial_camera_speed_ * delta_time;
}

void GLCameraMover::set_mouse_pos(const QPointF& pos)
{
	if(first_mouse_callback_) {
		last_mouse_pos_ = pos;
		first_mouse_callback_ = false;
		return;
	}

	update_camera_direction(pos);
	camera.update_camera_vectors();
}

void GLCameraMover::update_camera_zoom(const float dy)
{
	if(camera.zoom >= 1.f && camera.zoom <= 45.f) {
		camera.zoom -= dy;
	} else if(camera.zoom < 1.f) {
		camera.zoom = 1.f;
	} else {
		camera.zoom = 45.f;
	}
}

void GLCameraMover::set_key(const int key)
{
	last_pressed_key_ = key;
}

void GLCameraMover::reset_key(const int key)
{
	if(last_pressed_key_ == key) {
		last_pressed_key_ = std::numeric_limits<int>::max();
	}
}

void GLCameraMover::update_camera_pos(const float dx, const float dy)
{
	camera.yaw += dx;
	camera.pitch += dy;
	camera.pitch = std::clamp(camera.pitch, -89.0f, 89.0f);
}

void GLCameraMover::update_camera_direction(const QPointF& pos)
{
	auto x_offset = pos.x() - last_mouse_pos_.x();
	auto y_offset = last_mouse_pos_.y() - pos.y();
	last_mouse_pos_ = pos;

	const auto sensitivity = 0.05f;
	x_offset *= static_cast<qreal>(sensitivity);
	y_offset *= static_cast<qreal>(sensitivity);

	update_camera_pos(static_cast<float>(x_offset), static_cast<float>(y_offset));
}

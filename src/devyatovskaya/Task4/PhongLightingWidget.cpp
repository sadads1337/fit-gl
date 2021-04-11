#include <future>
#include <QStatusBar>

#include "PhongLightingWidget.h"
#include "ShaderCollection.h"


void PhongLightingWidget::show_render_dialog()
{
    render_dialog_.show();
}

void PhongLightingWidget::set_light_color(const QColor& color)
{
    for (auto& [light, light_object] : current_scene_.lights_objects) {
        light->color = color;

        for (auto& vertex : light_object->mesh.vertices) {
            vertex.color.setX(static_cast<float>(color.redF()));
        	vertex.color.setY(static_cast<float>(color.greenF()));
            vertex.color.setZ(static_cast<float>(color.blueF()));
        }

        light_object->renderer->reload();
    }
}

void PhongLightingWidget::set_ambient_color(const QColor& color)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.ambient = color;
        });
}

void PhongLightingWidget::set_diffuse_color(const QColor& color)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.diffuse = color;
        });
}

void PhongLightingWidget::set_specular_color(const QColor& color)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.specular = color;
        });
}

void PhongLightingWidget::set_shininess(const int shininess)
{
    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->material.shininess = static_cast<float>(shininess);
        });
}

void PhongLightingWidget::set_morph_factor(const int morph_factor)
{
    morph_factor_ = static_cast<float>(morph_factor) / 100.f;
}

void PhongLightingWidget::set_render_mode(const int state)
{
	auto* obj = sender();

	if(obj->objectName() == "fill_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_fill);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_fill);
        }
	} else if (obj->objectName() == "line_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_line);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_line);
        }
	} else if (obj->objectName() == "front_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_cull_face_front);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_cull_face_front);
        }
    } else {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_cull_face_back);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_cull_face_back);
        }
    }
}

void PhongLightingWidget::catch_fps(const QString& fps)
{
	emit send_fps(fps);
}


PhongLightingWidget::PhongLightingWidget(QWidget* parent)
	:   QOpenGLWidget{ parent },
		render_dialog_{*this },
		lighting_dialog_{*this},
		morphing_dialog_{ *this }
{
	setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
	connect(&fps_counter_, &FPSCounter::emit_fps, this, &PhongLightingWidget::catch_fps);
	
    connect(&light_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_light_color);
    connect(&ambient_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_ambient_color);
    connect(&diffuse_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_diffuse_color);
    connect(&specular_color_dialog_, &QColorDialog::currentColorChanged, this, &PhongLightingWidget::set_specular_color);

    light_color_dialog_.setWindowTitle("Light Color");
    ambient_color_dialog_.setWindowTitle("Ambient Color");
    diffuse_color_dialog_.setWindowTitle("Diffuse Color");
    specular_color_dialog_.setWindowTitle("Specular Color");
}


void PhongLightingWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_1) {
        makeCurrent();
        ++scene_count_;

    	
    	if(scene_count_ == prep_scenes_.scenes.size() - 1) {
            is_morphing_ = true;
    	}
    	
        lighting_dialog_.reset_state();
        const auto current_scene = std::next(prep_scenes_.scenes.begin(), scene_count_);
    	if(current_scene == prep_scenes_.scenes.end()) {
            scene_count_ = 0;
            current_scene_ = *prep_scenes_.scenes.begin();
            is_morphing_ = false;
    	} else {
            current_scene_ = *current_scene;
    	}
    } else {
        current_scene_.camera_mover.set_key(event->key());
    }
}



void PhongLightingWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!event->screenPos().isNull() && current_scene_.camera_mover.activated) {
        current_scene_.camera_mover.set_mouse_pos(event->screenPos());
    }
}

void PhongLightingWidget::mousePressEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton) {
        current_scene_.camera_mover.activated = true;
        current_scene_.camera_mover.set_mouse_pos(event->screenPos());
	}
}

void PhongLightingWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        current_scene_.camera_mover.activated = false;
    }
}


void PhongLightingWidget::wheelEvent(QWheelEvent* event)
{
    QPoint num_degrees = event->angleDelta() / 8;

    if (!num_degrees.isNull()) {
        QPoint num_steps = num_degrees / 15;
        current_scene_.camera_mover.update_camera_zoom(num_steps.y());
    }

    event->accept();
}




void PhongLightingWidget::keyReleaseEvent(QKeyEvent* event)
{
    current_scene_.camera_mover.reset_key(event->key());
}

void PhongLightingWidget::show_shininess_dialog()
{
    lighting_dialog_.show();
}

void PhongLightingWidget::show_light_color_dialog()
{
    light_color_dialog_.show();
}

void PhongLightingWidget::show_ambient_color_dialog()
{
    ambient_color_dialog_.show();
}

void PhongLightingWidget::show_diffuse_color_dialog()
{
    diffuse_color_dialog_.show();
}

void PhongLightingWidget::show_specular_color_dialog()
{
    specular_color_dialog_.show();
}

void PhongLightingWidget::show_morphing_widget()
{
    morphing_dialog_.show();
}

void PhongLightingWidget::initializeGL()
{

    const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());    

    renderer_.init(width(), height(), retina_scale);
    prep_scenes_.init();
    current_scene_ = *prep_scenes_.scenes.begin();

    timer_.start(16, this);
}

void PhongLightingWidget::paintGL()
{
    update_framerate();

    std::for_each(current_scene_.objects.begin(), current_scene_.objects.end(), [&](std::shared_ptr<GLObject>& object)
        {
            object->transform.rotate(100.f / 600.f, { 0, 0, -1});
            object->renderer->shader_program_->setUniformValue("morphFactor", morph_factor_);
        });
	
    renderer_.render(current_scene_);
}

void PhongLightingWidget::timerEvent(QTimerEvent*)
{
    current_scene_.camera_mover.set_camera_speed(fps_counter_.delta_time());
    current_scene_.camera_mover.move();
	update();
}

void PhongLightingWidget::update_framerate()
{
	fps_counter_.calculate_fps();
}

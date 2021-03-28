#include <future>
#include <QStatusBar>

#include "PhongLightingWidget.h"
#include "ShaderCollection.h"


void PhongLightingWidget::show_render_dialog()
{
    render_dialog_.show();
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

PhongLightingWidget::PhongLightingWidget(QWidget* parent)
	:   QOpenGLWidget{ parent },
        render_dialog_{*this }
{
	setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}


void PhongLightingWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_1) {
        makeCurrent();
        ++scene_count_;

    	
    	if(scene_count_ == prep_scenes_.scenes.size() - 1) {
            is_morphing_ = true;
    	}
    	
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

void PhongLightingWidget::show_morphing_widget()
{
    morphing_widget_.show();
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
    		if(is_morphing_) {
                object->renderer->shader_program_->setUniformValue("morphFactor", morph_factor_);
    		}
        });
	
    renderer_.render(current_scene_);
}

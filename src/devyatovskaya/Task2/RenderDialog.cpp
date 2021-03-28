#include "RenderDialog.h"
#include "PhongLightingWidget.h"

RenderDialog::RenderDialog(PhongLightingWidget& phong_widget, QWidget* parent)
	:	QWidget{ parent }
{
	setupUi(this);
	
	connect(fill_checkBox, &QCheckBox::stateChanged, &phong_widget, &PhongLightingWidget::set_render_mode);
	connect(line_checkBox, &QCheckBox::stateChanged, &phong_widget, &PhongLightingWidget::set_render_mode);
	connect(front_checkBox, &QCheckBox::stateChanged, &phong_widget, &PhongLightingWidget::set_render_mode);
	connect(back_checkBox, &QCheckBox::stateChanged, &phong_widget, &PhongLightingWidget::set_render_mode);
}

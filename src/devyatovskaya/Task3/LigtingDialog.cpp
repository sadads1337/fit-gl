#include "LightingDialog.h"
#include "PhongLightingWidget.h"

LightingDialog::LightingDialog(PhongLightingWidget &phong_widget,
                               QWidget *parent)
    : QWidget{parent} {
  setupUi(this);
  connect(shiness, &QSlider::valueChanged, &phong_widget,
          &PhongLightingWidget::set_shininess);
}

void LightingDialog::reset_state() { shiness->setValue(32); }

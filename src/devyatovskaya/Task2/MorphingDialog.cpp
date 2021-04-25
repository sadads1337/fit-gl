#include "MorphingDialog.h"
#include "PhongLightingWidget.h"

MorphingDialog::MorphingDialog(PhongLightingWidget &phong_widget,
                               QWidget *parent)
    : QWidget{parent} {
  setupUi(this);
  connect(morphing, &QSlider::valueChanged, &phong_widget,
          &PhongLightingWidget::set_morph_factor);
}
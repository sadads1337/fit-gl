#include "morphingwidget.h"

#include "cubewidget.h"


MorphingWidget::MorphingWidget(CubeWidget& cube_widget, QWidget* parent)
    : QWidget{ parent }
{
    setupUi(this);

    connect(MorphSlider, &QSlider::valueChanged, &cube_widget, &CubeWidget::set_morph_factor);
    connect(GridSlider, &QSlider::valueChanged, &cube_widget, &CubeWidget::update_grid);
}


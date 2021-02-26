#include "cubewidget.h"

CubeWidget::CubeWidget(QWidget* parent) : QWidget{ parent }
{
    initColorDialog();
    initSlidersDialog();

    layout_ = new QHBoxLayout;
    cube_window_ = new CubeWindow;
    time_slider_ = new QSlider;

    connect(color_dialog_, &QColorDialog::currentColorChanged, cube_window_, &CubeWindow::get_color);

    initCubeWindow();
    initLayout();
}

void CubeWidget::initCubeWindow()
{
    QSurfaceFormat format;
    format.setSamples(32);

    cube_window_->setFormat(format);
}

void CubeWidget::initColorDialog()
{
    color_dialog_->setGeometry(50, 50, 100, 100);
    color_dialog_->setOption(QColorDialog::NoButtons);
}

void CubeWidget::initLayout()
{
    layout_->addWidget(time_slider_);
    layout_->addWidget(color_dialog_);
    layout_->addWidget(cube_window_);

    setLayout(layout_);
}

void CubeWidget::initSlidersDialog()
{
    /*slider_x_.setOrientation(Qt::Orientation::Horizontal);
    slider_y_.setOrientation(Qt::Orientation::Horizontal);
    slider_z_.setOrientation(Qt::Orientation::Horizontal);
    slider_x_.setGeometry(50, 217, 230, 50);
    slider_y_.setGeometry(50, 234, 230, 50);
    slider_z_.setGeometry(50, 251, 230, 50);*/
}

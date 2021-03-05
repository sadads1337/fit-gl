//
// Created by nikita on 22.02.2021.
//

#include "Widget.h"
#include "Window.h"


Window::Window()
{
    widget = std::make_unique<Widget>();

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    xlabel = std::make_unique<QLabel>("X");
    ylabel = std::make_unique<QLabel>("Y");
    zlabel = std::make_unique<QLabel>("Z");
    color = std::make_unique<QColorDialog>();

    connect(xSlider.get(), &QSlider::valueChanged, widget.get(), &Widget::setXRotation);
    connect(ySlider.get(), &QSlider::valueChanged, widget.get(), &Widget::setYRotation);
    connect(zSlider.get(), &QSlider::valueChanged, widget.get(), &Widget::setZRotation);
    connect(color.get(), &QColorDialog::currentColorChanged, widget.get(), &Widget::setColor);

    mainLayout = std::make_unique<QVBoxLayout>();
    container = std::make_unique<QGridLayout>();
    container->addWidget(widget.get(),0, 0, 2, 1);
    container->addWidget(xSlider.get(),1, 1, 1, 1);
    container->addWidget(ySlider.get(),1, 2, 1, 1);
    container->addWidget(zSlider.get(),1, 3, 1, 1);
    container->addWidget(xlabel.get(),0, 1, 1, 1);
    container->addWidget(ylabel.get(),0, 2, 1, 1);
    container->addWidget(zlabel.get(),0, 3, 1, 1);
    container->addWidget(color.get(),2, 0, 1, 3);

    w = std::make_unique<QWidget>();
    w->setLayout(container.get());
    mainLayout->addWidget(w.get());
    setLayout(mainLayout.get());

    xSlider->setValue(50);
    ySlider->setValue(50);
    zSlider->setValue(50);
    color->setCurrentColor(QColor(Qt::gray));
}

std::unique_ptr<QSlider> Window::createSlider()
{
    auto slider = std::make_unique<QSlider>(Qt::Vertical);
    slider->setRange(0, 100);
    slider->setSingleStep(10);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}


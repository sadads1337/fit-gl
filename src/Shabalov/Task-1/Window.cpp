//
// Created by nikita on 22.02.2021.
//

#include "Widget.h"
#include "Window.h"
#include "MainWindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QColorDialog>

Window::Window(MainWindow *mw)
        : mainWindow(mw)
{
    widget = new Widget;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    QLabel *xlabel = new QLabel("X", this);
    QLabel *ylabel = new QLabel("Y", this);
    QLabel *zlabel = new QLabel("Z", this);
    QColorDialog *color = new QColorDialog(this);

    connect(xSlider, &QSlider::valueChanged, widget, &Widget::setXRotation);
    connect(ySlider, &QSlider::valueChanged, widget, &Widget::setYRotation);
    connect(zSlider, &QSlider::valueChanged, widget, &Widget::setZRotation);
    connect(color, &QColorDialog::currentColorChanged, widget, &Widget::setColor);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *container = new QGridLayout;
    container->addWidget(widget,0, 0, 2, 1);
    container->addWidget(xSlider,1, 1, 1, 1);
    container->addWidget(ySlider,1, 2, 1, 1);
    container->addWidget(zSlider,1, 3, 1, 1);
    container->addWidget(xlabel,0, 1, 1, 1);
    container->addWidget(ylabel,0, 2, 1, 1);
    container->addWidget(zlabel,0, 3, 1, 1);
    container->addWidget(color,2, 0, 1, 3);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    setLayout(mainLayout);

    xSlider->setValue(50);
    ySlider->setValue(50);
    zSlider->setValue(50);
    color->setCurrentColor(QColor(Qt::gray));
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 100);
    slider->setSingleStep(10);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}


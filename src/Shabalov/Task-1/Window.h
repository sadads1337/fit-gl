//
// Created by nikita on 22.02.2021.
//

#ifndef TASK_1_WINDOW_H
#define TASK_1_WINDOW_H


#include <QWidget>
#include <QSlider>
#include "Widget.h"

class Window : public QWidget
{
Q_OBJECT

public:
    Window();

private:
    QSlider *createSlider();

    Widget *widget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};



#endif //TASK_1_WINDOW_H

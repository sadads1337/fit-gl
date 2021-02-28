//
// Created by nikita on 22.02.2021.
//

#ifndef TASK_1_WINDOW_H
#define TASK_1_WINDOW_H


#include <QWidget>
#include <QSlider>
#include "MainWindow.h"
#include "Widget.h"

class Window : public QWidget
{
Q_OBJECT

public:
    Window(MainWindow *mw);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QSlider *createSlider();

    Widget *widget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    MainWindow *mainWindow;
};



#endif //TASK_1_WINDOW_H

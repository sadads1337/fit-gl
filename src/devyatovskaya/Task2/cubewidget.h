#pragma once
#include "cubewindow.h"
#include <QHBoxLayout>

//TODO: make "morph" class that would take any Geometry and morph it

class CubeWidget: public QWidget
{
    Q_OBJECT
public:
    CubeWidget(QWidget* parent = nullptr);

private:
    QColorDialog* color_dialog_{ new QColorDialog };
    CubeWindow* cube_window_;
    QSlider* time_slider_;

    QHBoxLayout* layout_;


    void initColorDialog();
    void initSlidersDialog();
    void initCubeWindow();
    void initLayout();
};

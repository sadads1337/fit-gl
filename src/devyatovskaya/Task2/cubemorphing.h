#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cubemorphing.h"

class CubeMorphing : public QMainWindow
{
    Q_OBJECT

public:
    CubeMorphing(QWidget *parent = Q_NULLPTR);

private:
    Ui::CubeMorphingClass ui;
};

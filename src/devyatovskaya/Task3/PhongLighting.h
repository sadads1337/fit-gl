#pragma once
#include "ui_PhongLighting.h"

class PhongLighting : public QMainWindow
{
    Q_OBJECT

public:
    PhongLighting(QWidget *parent = Q_NULLPTR);

	
private:
    Ui::PhongLightingClass ui;
};

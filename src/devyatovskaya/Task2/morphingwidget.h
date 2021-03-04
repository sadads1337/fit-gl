#pragma once
#include "ui_morphingwidget.h"

class CubeWidget;

class MorphingWidget : public QWidget, public Ui::Form
{

Q_OBJECT

public:
    explicit MorphingWidget(CubeWidget& cube_widget, QWidget* parent = nullptr);
};

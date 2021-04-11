#pragma once
#include <qobjectdefs.h>
#include "ui_MorphingDialog.h"

class PhongLightingWidget;

class MorphingDialog : public QWidget, public Ui::Morph
{
    Q_OBJECT
public:
    explicit MorphingDialog(PhongLightingWidget& phong_widget, QWidget* parent = nullptr);
};

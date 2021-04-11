#pragma once
#include <qobjectdefs.h>
#include "ui_LightingDialog.h"
class PhongLightingWidget;

class LightingDialog : public QWidget, public Ui::Form
{
    Q_OBJECT
public:
    explicit LightingDialog(PhongLightingWidget& phong_widget, QWidget* parent = nullptr);

    void reset_state();
};

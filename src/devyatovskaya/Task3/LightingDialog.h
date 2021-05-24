#pragma once
#include "ui_LightingDialog.h"
#include <qobjectdefs.h>
class PhongLightingWidget;

class LightingDialog : public QWidget, public Ui::Form {
  Q_OBJECT
public:
  explicit LightingDialog(PhongLightingWidget &phong_widget,
                          QWidget *parent = nullptr);

  void reset_state();
};

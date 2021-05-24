#pragma once
#include "ui_MorphingDialog.h"
#include <qobjectdefs.h>

class PhongLightingWidget;

class MorphingDialog : public QWidget, public Ui::Morph {
  Q_OBJECT
public:
  explicit MorphingDialog(PhongLightingWidget &phong_widget,
                          QWidget *parent = nullptr);
};

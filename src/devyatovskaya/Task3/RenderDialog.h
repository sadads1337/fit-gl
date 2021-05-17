#pragma once
#include "ui_RenderDialog.h"
#include <qobjectdefs.h>

class PhongLightingWidget;

class RenderDialog : public QWidget, public Ui::RenderDialog {
  Q_OBJECT
public:
  explicit RenderDialog(PhongLightingWidget &phong_widget,
                        QWidget *parent = nullptr);
};

#pragma once
#include "SquareWindow.hpp"
#include <QColorDialog>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <type_traits>

class MyWidget : public QWidget {
  Q_OBJECT

public:
  MyWidget();
};

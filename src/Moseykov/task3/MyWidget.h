#ifndef FIT_GL_MYWIDGET_H
#define FIT_GL_MYWIDGET_H

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

#endif // FIT_GL_MYWIDGET_H

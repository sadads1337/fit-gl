#ifndef FIT_GL_MYWIDGET_H
#define FIT_GL_MYWIDGET_H

#include "SquareWindow.hpp"
#include <type_traits>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QColorDialog>

class MyWidget: public QWidget {
  Q_OBJECT

public:
  MyWidget();
};

#endif // FIT_GL_MYWIDGET_H

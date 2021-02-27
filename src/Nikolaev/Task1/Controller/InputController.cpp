//
// Created by andre on 22.02.2021.
//

#include "InputController.h"

#include <utility>

void InputController::keyPressEvent(QKeyEvent *event) {
  pressedKeys.insert(event->key());
}

void InputController::keyReleaseEvent(QKeyEvent *event) {
  pressedKeys.erase(event->key());
}

void InputController::update() {
  float colorRate = 0.05f;

  if ((pressedKeys.find(Qt::Key::Key_Up) != pressedKeys.end())) {
    if (RGBcolors[0] < 1.0f)
      RGBcolors[0] += colorRate;
    else if (RGBcolors[1] < 1.0f)
      RGBcolors[1] += colorRate;
    else if (RGBcolors[2] < 1.0f)
      RGBcolors[2] += colorRate;
  }
  if ((pressedKeys.find(Qt::Key::Key_Down) != pressedKeys.end())) {
    if (RGBcolors[0] < 1.00f + colorRate && RGBcolors[0] > 0.0f - colorRate)
      RGBcolors[0] -= colorRate;
    else if (RGBcolors[1] < 1.0f + colorRate && RGBcolors[1] > 0.0f - colorRate)
      RGBcolors[1] -= colorRate;
    else if (RGBcolors[2] < 1.0f + colorRate && RGBcolors[2] > 0.0f - colorRate)
      RGBcolors[2] -= colorRate;
  }
}

QVector3D InputController::getRGBcolors() { return RGBcolors; }
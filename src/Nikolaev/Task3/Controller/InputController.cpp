#include "InputController.h"

void InputController::keyPressEvent(QKeyEvent *event) {
  int pressedKey = event->key();
  if(lastPressedKey != pressedKey) {
    if (pressedKey >= Qt::Key::Key_0 && pressedKey <= Qt::Key::Key_9) {
      vertexFactor = pressedKey - Qt::Key::Key_0;
    }
    else if (pressedKey == Qt::Key::Key_F) {
      currentShader = Phong;
    }
    else if (pressedKey == Qt::Key::Key_G) {
      currentShader = Gouraud;
    }
    swapKeyFlag = true;
  }
  lastPressedKey = pressedKey;
}
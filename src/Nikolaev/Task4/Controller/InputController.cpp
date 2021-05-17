#include "InputController.h"

#define NUM_TEXTURE_FILES 3

void InputController::keyPressEvent(QKeyEvent *event) {
  int pressedKey = event->key();

  if (pressedKey == Qt::Key::Key_Space) {
    currentTexture = (currentTexture + 1) % NUM_TEXTURE_FILES;
    swapKeyFlag = true;
  }

  if (lastPressedKey != pressedKey) {
    if (pressedKey >= Qt::Key::Key_0 && pressedKey <= Qt::Key::Key_9) {
      vertexFactor = pressedKey - Qt::Key::Key_0;
    } else if (pressedKey == Qt::Key::Key_F) {
      currentShader = Phong;
    } else if (pressedKey == Qt::Key::Key_G) {
      currentShader = Gouraud;
    }
    swapKeyFlag = true;
  }
  lastPressedKey = pressedKey;
}
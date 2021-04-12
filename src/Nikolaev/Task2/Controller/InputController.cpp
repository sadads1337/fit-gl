#include "InputController.h"

void InputController::keyPressEvent(QKeyEvent *event) {
  pressedKeys.insert(event->key());
}

void InputController::keyReleaseEvent(QKeyEvent *event) {
  pressedKeys.erase(event->key());
}

void InputController::update() {
  for(auto factor = 1U; factor < 10U; factor++){
    unsigned int key = Qt::Key::Key_0 + factor;
    if((pressedKeys.find(key) != pressedKeys.end())){
      vertexFactor = factor;
    }
  }
}
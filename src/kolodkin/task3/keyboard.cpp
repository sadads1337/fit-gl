#include "keyboard.hpp"

Keyboard::Keyboard(std::initializer_list<int> trackedKeys) {
  for (auto key : trackedKeys) {
    keysState[key] = false;
  }
}

bool Keyboard::getKeyState(int key) {
  if (keysState.find(key) == keysState.end())
    return false;

  return keysState[key];
}

bool Keyboard::operator[](int key) { return getKeyState(key); }

void Keyboard::setKeyState(int key, bool state) {
  if (keysState.find(key) == keysState.end())
    return;

  keysState[key] = state;
}

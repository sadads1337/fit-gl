#pragma once
#include <QKeyEvent>
#include <unordered_map>

class Keyboard {
public:
  Keyboard(std::initializer_list<int> trackedKeys);
  bool getKeyState(int key);
  bool operator[](int key);
  void setKeyState(int key, bool state);

private:
  std::unordered_map<int, bool> keysState;
};

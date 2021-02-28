//
// Created by andre on 22.02.2021.
//

#ifndef FIT_GL_INPUTCONTROLLER_H
#define FIT_GL_INPUTCONTROLLER_H

#include <memory>
#include <unordered_set>

#include <QKeyEvent>
#include <QVector3D>

class InputController {
public:
  void keyPressEvent(QKeyEvent *event);

  void keyReleaseEvent(QKeyEvent *event);

  void update();

  QVector3D getRGBcolors();

private:
  std::unordered_set<int> pressedKeys;

  QVector3D RGBcolors = {0.0f, 0.0f, 0.0f};
};

#endif // FIT_GL_INPUTCONTROLLER_H

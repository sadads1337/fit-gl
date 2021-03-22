#include "MainWindow.h"
#include "Window.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow() {
  if (!centralWidget())
    setCentralWidget(new Window());
  else
    QMessageBox::information(nullptr, tr("Cannot add new window"),
                             tr("Already occupied. Undock first."));
}
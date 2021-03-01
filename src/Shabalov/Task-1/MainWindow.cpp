//
// Created by nikita on 22.02.2021.
//

#include "MainWindow.h"
#include "Window.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>

MainWindow::MainWindow()
{
    if (!centralWidget())
        setCentralWidget(new Window());
    else
        QMessageBox::information(nullptr, tr("Cannot add new window"),tr("Already occupied. Undock first."));
}
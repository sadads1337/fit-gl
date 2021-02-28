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
    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&Cube"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    connect(addNew, &QAction::triggered, this, &MainWindow::onAddNew);
    setMenuBar(menuBar);

    onAddNew();
}

void MainWindow::onAddNew() {
    if (!centralWidget())
        setCentralWidget(new Window(this));
    else
        QMessageBox::information(nullptr, tr("Cannot add new window"),
                                 tr("Already occupied. Undock first."));
}
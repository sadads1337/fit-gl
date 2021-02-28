//
// Created by nikita on 22.02.2021.
//

#ifndef TASK_1_MAINWINDOW_H
#define TASK_1_MAINWINDOW_H


#include <QMainWindow>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

private slots:
    void onAddNew();
};


#endif //TASK_1_MAINWINDOW_H

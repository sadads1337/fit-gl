#ifndef UNTITLED4_MAINWINDOW_H
#define UNTITLED4_MAINWINDOW_H

#include <QWidget>
//Ui_MainWindow
//mainwindow
QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QWidget {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);

    ~mainwindow() override;

private:
    Ui::mainwindow *ui = nullptr;
};

#endif //UNTITLED4_MAINWINDOW_H

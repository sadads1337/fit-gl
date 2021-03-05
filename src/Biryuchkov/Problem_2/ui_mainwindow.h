/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cubewidget.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *morphFactorLabel;
    QHBoxLayout *horizontalLayout_2;
    QSlider *morphFactorSlider;
    QLabel *morphFactorNumLabel;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QSlider *horizontalSlider;
    QLabel *gridStepsLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLabel *colorChangeLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *facesButton;
    QPushButton *edgesButton;
    QLabel *colorChangeLable;
    QSpinBox *faceNumSpinbox;
    CubeWidget *cubeWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(777, 663);
        MainWindow->setMinimumSize(QSize(640, 640));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QPushButton{}"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        morphFactorLabel = new QLabel(centralwidget);
        morphFactorLabel->setObjectName(QString::fromUtf8("morphFactorLabel"));
        morphFactorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(morphFactorLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        morphFactorSlider = new QSlider(centralwidget);
        morphFactorSlider->setObjectName(QString::fromUtf8("morphFactorSlider"));
        morphFactorSlider->setMinimum(0);
        morphFactorSlider->setMaximum(50);
        morphFactorSlider->setOrientation(Qt::Horizontal);
        morphFactorSlider->setTickPosition(QSlider::TicksBelow);
        morphFactorSlider->setTickInterval(2);

        horizontalLayout_2->addWidget(morphFactorSlider);

        morphFactorNumLabel = new QLabel(centralwidget);
        morphFactorNumLabel->setObjectName(QString::fromUtf8("morphFactorNumLabel"));
        morphFactorNumLabel->setFrameShape(QFrame::Box);
        morphFactorNumLabel->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(morphFactorNumLabel);


        verticalLayout_5->addLayout(horizontalLayout_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setFocusPolicy(Qt::WheelFocus);
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(20);
        horizontalSlider->setValue(8);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(1);

        horizontalLayout_4->addWidget(horizontalSlider);

        gridStepsLabel = new QLabel(centralwidget);
        gridStepsLabel->setObjectName(QString::fromUtf8("gridStepsLabel"));
        gridStepsLabel->setFrameShape(QFrame::Box);
        gridStepsLabel->setFrameShadow(QFrame::Raised);

        horizontalLayout_4->addWidget(gridStepsLabel);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        colorChangeLabel = new QLabel(centralwidget);
        colorChangeLabel->setObjectName(QString::fromUtf8("colorChangeLabel"));
        colorChangeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(colorChangeLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        facesButton = new QPushButton(centralwidget);
        facesButton->setObjectName(QString::fromUtf8("facesButton"));
        facesButton->setAutoFillBackground(false);

        horizontalLayout_5->addWidget(facesButton);

        edgesButton = new QPushButton(centralwidget);
        edgesButton->setObjectName(QString::fromUtf8("edgesButton"));

        horizontalLayout_5->addWidget(edgesButton);


        verticalLayout->addLayout(horizontalLayout_5);

        colorChangeLable = new QLabel(centralwidget);
        colorChangeLable->setObjectName(QString::fromUtf8("colorChangeLable"));

        verticalLayout->addWidget(colorChangeLable);

        faceNumSpinbox = new QSpinBox(centralwidget);
        faceNumSpinbox->setObjectName(QString::fromUtf8("faceNumSpinbox"));
        faceNumSpinbox->setMinimum(-1);
        faceNumSpinbox->setMaximum(5);
        faceNumSpinbox->setValue(-1);

        verticalLayout->addWidget(faceNumSpinbox);


        verticalLayout_4->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        cubeWidget = new CubeWidget(centralwidget);
        cubeWidget->setObjectName(QString::fromUtf8("cubeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(cubeWidget->sizePolicy().hasHeightForWidth());
        cubeWidget->setSizePolicy(sizePolicy);
        cubeWidget->setMinimumSize(QSize(640, 480));
        cubeWidget->setFocusPolicy(Qt::StrongFocus);

        verticalLayout_2->addWidget(cubeWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 777, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(cubeWidget, morphFactorSlider);
        QWidget::setTabOrder(morphFactorSlider, horizontalSlider);
        QWidget::setTabOrder(horizontalSlider, facesButton);
        QWidget::setTabOrder(facesButton, edgesButton);
        QWidget::setTabOrder(edgesButton, faceNumSpinbox);

        retranslateUi(MainWindow);
        QObject::connect(morphFactorSlider, SIGNAL(valueChanged(int)), morphFactorNumLabel, SLOT(setNum(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), gridStepsLabel, SLOT(setNum(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(makeNewGrid(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        morphFactorLabel->setText(QApplication::translate("MainWindow", "Morph factor", nullptr));
        morphFactorNumLabel->setText(QApplication::translate("MainWindow", "0.00", nullptr));
        label->setText(QApplication::translate("MainWindow", "Grid steps", nullptr));
        gridStepsLabel->setText(QApplication::translate("MainWindow", "8", nullptr));
        colorChangeLabel->setText(QApplication::translate("MainWindow", "Color Change", nullptr));
        facesButton->setText(QApplication::translate("MainWindow", "Faces", nullptr));
        edgesButton->setText(QApplication::translate("MainWindow", "Edges", nullptr));
        colorChangeLable->setText(QApplication::translate("MainWindow", "Current cube's face", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

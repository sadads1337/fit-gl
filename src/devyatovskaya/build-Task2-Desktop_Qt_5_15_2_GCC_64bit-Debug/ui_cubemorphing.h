/********************************************************************************
** Form generated from reading UI file 'cubemorphing.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUBEMORPHING_H
#define UI_CUBEMORPHING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cubewidget.h"

QT_BEGIN_NAMESPACE

class Ui_CubeMorphingClass
{
public:
    QAction *actionMorphing;
    QAction *actionSet_Random_Color;
    QAction *actionSet_Specific_Color;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    CubeWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menu_Functions;
    QMenu *menuChange_Color;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CubeMorphingClass)
    {
        if (CubeMorphingClass->objectName().isEmpty())
            CubeMorphingClass->setObjectName(QString::fromUtf8("CubeMorphingClass"));
        CubeMorphingClass->resize(600, 400);
        actionMorphing = new QAction(CubeMorphingClass);
        actionMorphing->setObjectName(QString::fromUtf8("actionMorphing"));
        actionSet_Random_Color = new QAction(CubeMorphingClass);
        actionSet_Random_Color->setObjectName(QString::fromUtf8("actionSet_Random_Color"));
        actionSet_Specific_Color = new QAction(CubeMorphingClass);
        actionSet_Specific_Color->setObjectName(QString::fromUtf8("actionSet_Specific_Color"));
        centralWidget = new QWidget(CubeMorphingClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        openGLWidget = new CubeWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        CubeMorphingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CubeMorphingClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        menu_Functions = new QMenu(menuBar);
        menu_Functions->setObjectName(QString::fromUtf8("menu_Functions"));
        menuChange_Color = new QMenu(menu_Functions);
        menuChange_Color->setObjectName(QString::fromUtf8("menuChange_Color"));
        CubeMorphingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CubeMorphingClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CubeMorphingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CubeMorphingClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CubeMorphingClass->setStatusBar(statusBar);

        menuBar->addAction(menu_Functions->menuAction());
        menu_Functions->addAction(menuChange_Color->menuAction());
        menu_Functions->addAction(actionMorphing);
        menuChange_Color->addAction(actionSet_Specific_Color);
        menuChange_Color->addAction(actionSet_Random_Color);

        retranslateUi(CubeMorphingClass);
        QObject::connect(actionSet_Specific_Color, SIGNAL(triggered()), openGLWidget, SLOT(show_color_dialog()));
        QObject::connect(actionMorphing, SIGNAL(triggered()), openGLWidget, SLOT(show_morph_dialog()));
        QObject::connect(actionSet_Random_Color, SIGNAL(triggered()), openGLWidget, SLOT(set_random_color()));

        QMetaObject::connectSlotsByName(CubeMorphingClass);
    } // setupUi

    void retranslateUi(QMainWindow *CubeMorphingClass)
    {
        CubeMorphingClass->setWindowTitle(QCoreApplication::translate("CubeMorphingClass", "CubeMorphing", nullptr));
        actionMorphing->setText(QCoreApplication::translate("CubeMorphingClass", "Morphing", nullptr));
        actionSet_Random_Color->setText(QCoreApplication::translate("CubeMorphingClass", "Set Random Color", nullptr));
        actionSet_Specific_Color->setText(QCoreApplication::translate("CubeMorphingClass", "Set Specific Color", nullptr));
        menu_Functions->setTitle(QCoreApplication::translate("CubeMorphingClass", " Functions", nullptr));
        menuChange_Color->setTitle(QCoreApplication::translate("CubeMorphingClass", "Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CubeMorphingClass: public Ui_CubeMorphingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUBEMORPHING_H

/********************************************************************************
** Form generated from reading UI file 'PhongLighting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHONGLIGHTING_H
#define UI_PHONGLIGHTING_H

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
#include "PhongLightingWidget.h"

QT_BEGIN_NAMESPACE

class Ui_PhongLightingClass
{
public:
    QAction *actionset_specific_color;
    QAction *actionset_render_mode;
    QAction *actionLightingDialog;
    QAction *actionAmbientDialog;
    QAction *actionDiffuseDialog;
    QAction *actionSpecularDialog;
    QAction *actionLightColorDialog;
    QAction *actionShininessDialog;
    QAction *actionset_morph_factor;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    PhongLightingWidget *PhongLightingWidget_;
    QMenuBar *menuBar;
    QMenu *menuFunctions;
    QMenu *menuRendering;
    QMenu *menuLighting;
    QMenu *menuMorphing;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PhongLightingClass)
    {
        if (PhongLightingClass->objectName().isEmpty())
            PhongLightingClass->setObjectName(QString::fromUtf8("PhongLightingClass"));
        PhongLightingClass->resize(600, 399);
        actionset_specific_color = new QAction(PhongLightingClass);
        actionset_specific_color->setObjectName(QString::fromUtf8("actionset_specific_color"));
        actionset_render_mode = new QAction(PhongLightingClass);
        actionset_render_mode->setObjectName(QString::fromUtf8("actionset_render_mode"));
        actionLightingDialog = new QAction(PhongLightingClass);
        actionLightingDialog->setObjectName(QString::fromUtf8("actionLightingDialog"));
        actionAmbientDialog = new QAction(PhongLightingClass);
        actionAmbientDialog->setObjectName(QString::fromUtf8("actionAmbientDialog"));
        actionDiffuseDialog = new QAction(PhongLightingClass);
        actionDiffuseDialog->setObjectName(QString::fromUtf8("actionDiffuseDialog"));
        actionSpecularDialog = new QAction(PhongLightingClass);
        actionSpecularDialog->setObjectName(QString::fromUtf8("actionSpecularDialog"));
        actionLightColorDialog = new QAction(PhongLightingClass);
        actionLightColorDialog->setObjectName(QString::fromUtf8("actionLightColorDialog"));
        actionShininessDialog = new QAction(PhongLightingClass);
        actionShininessDialog->setObjectName(QString::fromUtf8("actionShininessDialog"));
        actionset_morph_factor = new QAction(PhongLightingClass);
        actionset_morph_factor->setObjectName(QString::fromUtf8("actionset_morph_factor"));
        centralWidget = new QWidget(PhongLightingClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        PhongLightingWidget_ = new PhongLightingWidget(centralWidget);
        PhongLightingWidget_->setObjectName(QString::fromUtf8("PhongLightingWidget_"));

        verticalLayout->addWidget(PhongLightingWidget_);

        PhongLightingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PhongLightingClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFunctions = new QMenu(menuBar);
        menuFunctions->setObjectName(QString::fromUtf8("menuFunctions"));
        menuRendering = new QMenu(menuFunctions);
        menuRendering->setObjectName(QString::fromUtf8("menuRendering"));
        menuLighting = new QMenu(menuFunctions);
        menuLighting->setObjectName(QString::fromUtf8("menuLighting"));
        menuMorphing = new QMenu(menuFunctions);
        menuMorphing->setObjectName(QString::fromUtf8("menuMorphing"));
        PhongLightingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PhongLightingClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PhongLightingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PhongLightingClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PhongLightingClass->setStatusBar(statusBar);

        menuBar->addAction(menuFunctions->menuAction());
        menuFunctions->addAction(menuRendering->menuAction());
        menuFunctions->addAction(menuLighting->menuAction());
        menuFunctions->addAction(menuMorphing->menuAction());
        menuRendering->addAction(actionset_render_mode);
        menuLighting->addAction(actionAmbientDialog);
        menuLighting->addAction(actionDiffuseDialog);
        menuLighting->addAction(actionSpecularDialog);
        menuLighting->addAction(actionLightColorDialog);
        menuLighting->addAction(actionShininessDialog);
        menuMorphing->addAction(actionset_morph_factor);

        retranslateUi(PhongLightingClass);
        QObject::connect(PhongLightingWidget_, SIGNAL(send_fps(QString)), statusBar, SLOT(showMessage(QString)));
        QObject::connect(actionAmbientDialog, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_ambient_color_dialog()));
        QObject::connect(actionSpecularDialog, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_specular_color_dialog()));
        QObject::connect(actionDiffuseDialog, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_diffuse_color_dialog()));
        QObject::connect(actionLightColorDialog, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_light_color_dialog()));
        QObject::connect(actionShininessDialog, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_shininess_dialog()));
        QObject::connect(actionset_render_mode, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_render_dialog()));
        QObject::connect(actionset_morph_factor, SIGNAL(triggered()), PhongLightingWidget_, SLOT(show_morphing_widget()));

        QMetaObject::connectSlotsByName(PhongLightingClass);
    } // setupUi

    void retranslateUi(QMainWindow *PhongLightingClass)
    {
        PhongLightingClass->setWindowTitle(QCoreApplication::translate("PhongLightingClass", "PhongLighting", nullptr));
        actionset_specific_color->setText(QCoreApplication::translate("PhongLightingClass", "set specific color", nullptr));
        actionset_render_mode->setText(QCoreApplication::translate("PhongLightingClass", "set render mode", nullptr));
        actionLightingDialog->setText(QCoreApplication::translate("PhongLightingClass", "ShininessDialog", nullptr));
        actionAmbientDialog->setText(QCoreApplication::translate("PhongLightingClass", "AmbientDialog", nullptr));
        actionDiffuseDialog->setText(QCoreApplication::translate("PhongLightingClass", "DiffuseDialog", nullptr));
        actionSpecularDialog->setText(QCoreApplication::translate("PhongLightingClass", "SpecularDialog", nullptr));
        actionLightColorDialog->setText(QCoreApplication::translate("PhongLightingClass", "LightColorDialog", nullptr));
        actionShininessDialog->setText(QCoreApplication::translate("PhongLightingClass", "ShininessDialog", nullptr));
        actionset_morph_factor->setText(QCoreApplication::translate("PhongLightingClass", "set morph factor", nullptr));
        menuFunctions->setTitle(QCoreApplication::translate("PhongLightingClass", "Functions", nullptr));
        menuRendering->setTitle(QCoreApplication::translate("PhongLightingClass", "Rendering", nullptr));
        menuLighting->setTitle(QCoreApplication::translate("PhongLightingClass", "Lighting", nullptr));
        menuMorphing->setTitle(QCoreApplication::translate("PhongLightingClass", "Morphing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PhongLightingClass: public Ui_PhongLightingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHONGLIGHTING_H

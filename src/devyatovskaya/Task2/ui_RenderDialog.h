/********************************************************************************
** Form generated from reading UI file 'RenderDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERDIALOG_H
#define UI_RENDERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *fill_checkBox;
    QCheckBox *line_checkBox;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *front_checkBox;
    QCheckBox *back_checkBox;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *RenderDialog)
    {
        if (RenderDialog->objectName().isEmpty())
            RenderDialog->setObjectName(QString::fromUtf8("RenderDialog"));
        RenderDialog->resize(266, 254);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RenderDialog->sizePolicy().hasHeightForWidth());
        RenderDialog->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(RenderDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(RenderDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        fill_checkBox = new QCheckBox(RenderDialog);
        fill_checkBox->setObjectName(QString::fromUtf8("fill_checkBox"));
        fill_checkBox->setChecked(true);
        fill_checkBox->setTristate(false);

        horizontalLayout->addWidget(fill_checkBox);

        line_checkBox = new QCheckBox(RenderDialog);
        line_checkBox->setObjectName(QString::fromUtf8("line_checkBox"));
        line_checkBox->setChecked(false);

        horizontalLayout->addWidget(line_checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(RenderDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        front_checkBox = new QCheckBox(RenderDialog);
        front_checkBox->setObjectName(QString::fromUtf8("front_checkBox"));

        horizontalLayout_2->addWidget(front_checkBox);

        back_checkBox = new QCheckBox(RenderDialog);
        back_checkBox->setObjectName(QString::fromUtf8("back_checkBox"));
        back_checkBox->setChecked(true);

        horizontalLayout_2->addWidget(back_checkBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(RenderDialog);

        QMetaObject::connectSlotsByName(RenderDialog);
    } // setupUi

    void retranslateUi(QWidget *RenderDialog)
    {
        RenderDialog->setWindowTitle(QCoreApplication::translate("RenderDialog", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("RenderDialog", "glPolygonMode", nullptr));
        fill_checkBox->setText(QCoreApplication::translate("RenderDialog", "GL FILL", nullptr));
        line_checkBox->setText(QCoreApplication::translate("RenderDialog", "GL_LINE", nullptr));
        label->setText(QCoreApplication::translate("RenderDialog", "glCullFace", nullptr));
        front_checkBox->setText(QCoreApplication::translate("RenderDialog", "GL_FRONT", nullptr));
        back_checkBox->setText(QCoreApplication::translate("RenderDialog", "GL_BACK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RenderDialog: public Ui_RenderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERDIALOG_H

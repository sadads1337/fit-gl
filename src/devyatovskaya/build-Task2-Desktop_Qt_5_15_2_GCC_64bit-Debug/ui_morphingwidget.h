/********************************************************************************
** Form generated from reading UI file 'morphingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MORPHINGWIDGET_H
#define UI_MORPHINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSlider *MorphSlider;
    QLabel *label_2;
    QSlider *GridSlider;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QLCDNumber *MorphNumber;
    QSpacerItem *verticalSpacer_3;
    QLCDNumber *GridNumber;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(489, 235);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLineWidth(2);
        label->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(label);

        MorphSlider = new QSlider(Form);
        MorphSlider->setObjectName(QString::fromUtf8("MorphSlider"));
        MorphSlider->setMaximum(100);
        MorphSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(MorphSlider);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        GridSlider = new QSlider(Form);
        GridSlider->setObjectName(QString::fromUtf8("GridSlider"));
        GridSlider->setMaximum(100);
        GridSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(GridSlider);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        MorphNumber = new QLCDNumber(Form);
        MorphNumber->setObjectName(QString::fromUtf8("MorphNumber"));
        MorphNumber->setSmallDecimalPoint(true);
        MorphNumber->setSegmentStyle(QLCDNumber::Filled);

        verticalLayout_2->addWidget(MorphNumber);

        verticalSpacer_3 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        GridNumber = new QLCDNumber(Form);
        GridNumber->setObjectName(QString::fromUtf8("GridNumber"));

        verticalLayout_2->addWidget(GridNumber);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(Form);
        QObject::connect(GridSlider, SIGNAL(valueChanged(int)), GridNumber, SLOT(display(int)));
        QObject::connect(MorphSlider, SIGNAL(valueChanged(int)), MorphNumber, SLOT(display(int)));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "<html><head/><body><p><span style=\" font-size:11pt;\">Morph Factor</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "<html><head/><body><p><span style=\" font-size:11pt;\">Grid Step</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MORPHINGWIDGET_H

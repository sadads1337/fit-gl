/********************************************************************************
** Form generated from reading UI file 'MorphingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MORPHINGDIALOG_H
#define UI_MORPHINGDIALOG_H

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

class Ui_Morph
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSlider *morphing;
    QLCDNumber *number_shiness;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Morph)
    {
        if (Morph->objectName().isEmpty())
            Morph->setObjectName(QString::fromUtf8("Morph"));
        Morph->resize(486, 106);
        verticalLayout_2 = new QVBoxLayout(Morph);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Morph);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        morphing = new QSlider(Morph);
        morphing->setObjectName(QString::fromUtf8("morphing"));
        morphing->setMinimum(1);
        morphing->setMaximum(100);
        morphing->setValue(1);
        morphing->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(morphing);


        horizontalLayout->addLayout(verticalLayout);

        number_shiness = new QLCDNumber(Morph);
        number_shiness->setObjectName(QString::fromUtf8("number_shiness"));
        number_shiness->setProperty("value", QVariant(1.000000000000000));
        number_shiness->setProperty("intValue", QVariant(1));

        horizontalLayout->addWidget(number_shiness);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(Morph);
        QObject::connect(morphing, SIGNAL(valueChanged(int)), number_shiness, SLOT(display(int)));

        QMetaObject::connectSlotsByName(Morph);
    } // setupUi

    void retranslateUi(QWidget *Morph)
    {
        Morph->setWindowTitle(QCoreApplication::translate("Morph", "Form", nullptr));
        label->setText(QCoreApplication::translate("Morph", "Morph Factor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Morph: public Ui_Morph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MORPHINGDIALOG_H

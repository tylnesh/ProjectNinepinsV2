/********************************************************************************
** Form generated from reading UI file 'delay.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAY_H
#define UI_DELAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Delay
{
public:
    QLabel *label;

    void setupUi(QDialog *Delay)
    {
        if (Delay->objectName().isEmpty())
            Delay->setObjectName(QString::fromUtf8("Delay"));
        Delay->resize(1024, 600);
        label = new QLabel(Delay);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 220, 1531, 400));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(72);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);

        retranslateUi(Delay);

        QMetaObject::connectSlotsByName(Delay);
    } // setupUi

    void retranslateUi(QDialog *Delay)
    {
        Delay->setWindowTitle(QApplication::translate("Delay", "DELAY", nullptr));
        label->setText(QApplication::translate("Delay", "Na\304\215\303\255tavam...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Delay: public Ui_Delay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAY_H
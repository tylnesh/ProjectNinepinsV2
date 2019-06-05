/********************************************************************************
** Form generated from reading UI file 'fault.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAULT_H
#define UI_FAULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_fault
{
public:
    QPushButton *faultConfirmedButton;
    QPushButton *faultCancelledButton;

    void setupUi(QDialog *fault)
    {
        if (fault->objectName().isEmpty())
            fault->setObjectName(QStringLiteral("fault"));
        fault->resize(1024, 600);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(161, 161, 161, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        fault->setPalette(palette);
        faultConfirmedButton = new QPushButton(fault);
        faultConfirmedButton->setObjectName(QStringLiteral("faultConfirmedButton"));
        faultConfirmedButton->setGeometry(QRect(0, 20, 1171, 321));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        faultConfirmedButton->setPalette(palette1);
        QFont font;
        font.setPointSize(50);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        faultConfirmedButton->setFont(font);
        faultConfirmedButton->setAutoFillBackground(true);
        faultConfirmedButton->setFlat(true);
        faultCancelledButton = new QPushButton(fault);
        faultCancelledButton->setObjectName(QStringLiteral("faultCancelledButton"));
        faultCancelledButton->setGeometry(QRect(-30, 340, 1161, 311));
        QPalette palette2;
        QBrush brush3(QColor(0, 255, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush3);
        faultCancelledButton->setPalette(palette2);
        QFont font1;
        font1.setPointSize(50);
        font1.setBold(true);
        font1.setWeight(75);
        faultCancelledButton->setFont(font1);
        faultCancelledButton->setFlat(false);

        retranslateUi(fault);

        faultConfirmedButton->setDefault(false);


        QMetaObject::connectSlotsByName(fault);
    } // setupUi

    void retranslateUi(QDialog *fault)
    {
        fault->setWindowTitle(QApplication::translate("fault", "Dialog", 0));
        faultConfirmedButton->setText(QApplication::translate("fault", "Potvrdenie chyby", 0));
        faultCancelledButton->setText(QApplication::translate("fault", "Zru\305\241enie chyby", 0));
    } // retranslateUi

};

namespace Ui {
    class fault: public Ui_fault {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAULT_H

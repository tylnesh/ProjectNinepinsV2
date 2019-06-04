/********************************************************************************
** Form generated from reading UI file 'isgreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISGREEN_H
#define UI_ISGREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_IsGreen
{
public:
    QLabel *label;
    QPushButton *yesButton;
    QPushButton *noButton;

    void setupUi(QDialog *IsGreen)
    {
        if (IsGreen->objectName().isEmpty())
            IsGreen->setObjectName(QString::fromUtf8("IsGreen"));
        IsGreen->resize(640, 480);
        label = new QLabel(IsGreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 200, 351, 101));
        QFont font;
        font.setPointSize(32);
        label->setFont(font);
        label->setScaledContents(true);
        yesButton = new QPushButton(IsGreen);
        yesButton->setObjectName(QString::fromUtf8("yesButton"));
        yesButton->setGeometry(QRect(40, 330, 221, 81));
        QFont font1;
        font1.setPointSize(24);
        yesButton->setFont(font1);
        noButton = new QPushButton(IsGreen);
        noButton->setObjectName(QString::fromUtf8("noButton"));
        noButton->setGeometry(QRect(430, 330, 221, 81));
        noButton->setFont(font1);

        retranslateUi(IsGreen);

        QMetaObject::connectSlotsByName(IsGreen);
    } // setupUi

    void retranslateUi(QDialog *IsGreen)
    {
        IsGreen->setWindowTitle(QApplication::translate("IsGreen", "Dialog", nullptr));
        label->setText(QApplication::translate("IsGreen", "SVIETI ZELENA?", nullptr));
        yesButton->setText(QApplication::translate("IsGreen", "ANO", nullptr));
        noButton->setText(QApplication::translate("IsGreen", "NIE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IsGreen: public Ui_IsGreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISGREEN_H

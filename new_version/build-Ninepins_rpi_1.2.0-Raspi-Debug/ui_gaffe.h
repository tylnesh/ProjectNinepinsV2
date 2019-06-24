/********************************************************************************
** Form generated from reading UI file 'gaffe.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAFFE_H
#define UI_GAFFE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_gaffe
{
public:
    QPushButton *gaffeConfirmedButton;
    QPushButton *gaffeCancelledButton;

    void setupUi(QDialog *gaffe)
    {
        if (gaffe->objectName().isEmpty())
            gaffe->setObjectName(QString::fromUtf8("gaffe"));
        gaffe->resize(1024, 600);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(255, 255, 255, 128));
        brush1.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        QBrush brush3(QColor(161, 161, 161, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        gaffe->setPalette(palette);
        gaffeConfirmedButton = new QPushButton(gaffe);
        gaffeConfirmedButton->setObjectName(QString::fromUtf8("gaffeConfirmedButton"));
        gaffeConfirmedButton->setGeometry(QRect(0, 20, 1171, 321));
        QPalette palette1;
        QBrush brush5(QColor(255, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(255, 255, 255, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush6);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush7(QColor(255, 255, 255, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        gaffeConfirmedButton->setPalette(palette1);
        QFont font;
        font.setPointSize(50);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        gaffeConfirmedButton->setFont(font);
        gaffeConfirmedButton->setAutoFillBackground(true);
        gaffeConfirmedButton->setFlat(true);
        gaffeCancelledButton = new QPushButton(gaffe);
        gaffeCancelledButton->setObjectName(QString::fromUtf8("gaffeCancelledButton"));
        gaffeCancelledButton->setGeometry(QRect(-30, 340, 1161, 311));
        QPalette palette2;
        QBrush brush9(QColor(0, 255, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        gaffeCancelledButton->setPalette(palette2);
        QFont font1;
        font1.setPointSize(50);
        font1.setBold(true);
        font1.setWeight(75);
        gaffeCancelledButton->setFont(font1);
        gaffeCancelledButton->setFlat(false);

        retranslateUi(gaffe);

        gaffeConfirmedButton->setDefault(false);


        QMetaObject::connectSlotsByName(gaffe);
    } // setupUi

    void retranslateUi(QDialog *gaffe)
    {
        gaffe->setWindowTitle(QApplication::translate("gaffe", "Dialog", nullptr));
        gaffeConfirmedButton->setText(QApplication::translate("gaffe", "Potvrdenie chyby", nullptr));
        gaffeCancelledButton->setText(QApplication::translate("gaffe", "Zru\305\241enie chyby", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gaffe: public Ui_gaffe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAFFE_H

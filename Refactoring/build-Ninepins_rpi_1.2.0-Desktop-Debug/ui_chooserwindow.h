/********************************************************************************
** Form generated from reading UI file 'chooserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSERWINDOW_H
#define UI_CHOOSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooserWindow
{
public:
    QPushButton *practiceButton;
    QPushButton *partialgameButton;
    QPushButton *fullgameButton;
    QPushButton *shutdownButton;

    void setupUi(QDialog *ChooserWindow)
    {
        if (ChooserWindow->objectName().isEmpty())
            ChooserWindow->setObjectName(QString::fromUtf8("ChooserWindow"));
        ChooserWindow->resize(1024, 600);
        practiceButton = new QPushButton(ChooserWindow);
        practiceButton->setObjectName(QString::fromUtf8("practiceButton"));
        practiceButton->setEnabled(false);
        practiceButton->setGeometry(QRect(110, 350, 300, 180));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(40);
        font.setBold(false);
        font.setWeight(50);
        practiceButton->setFont(font);
        partialgameButton = new QPushButton(ChooserWindow);
        partialgameButton->setObjectName(QString::fromUtf8("partialgameButton"));
        partialgameButton->setGeometry(QRect(630, 80, 300, 180));
        partialgameButton->setFont(font);
        fullgameButton = new QPushButton(ChooserWindow);
        fullgameButton->setObjectName(QString::fromUtf8("fullgameButton"));
        fullgameButton->setGeometry(QRect(110, 80, 300, 180));
        fullgameButton->setFont(font);
        shutdownButton = new QPushButton(ChooserWindow);
        shutdownButton->setObjectName(QString::fromUtf8("shutdownButton"));
        shutdownButton->setGeometry(QRect(630, 350, 300, 180));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush3(QColor(255, 255, 255, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush4(QColor(161, 161, 161, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        shutdownButton->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(40);
        shutdownButton->setFont(font1);
        shutdownButton->setAutoDefault(true);
        shutdownButton->setFlat(false);

        retranslateUi(ChooserWindow);

        shutdownButton->setDefault(true);


        QMetaObject::connectSlotsByName(ChooserWindow);
    } // setupUi

    void retranslateUi(QDialog *ChooserWindow)
    {
        ChooserWindow->setWindowTitle(QApplication::translate("ChooserWindow", "Dialog", nullptr));
        practiceButton->setText(QApplication::translate("ChooserWindow", "Tr\303\251ning", nullptr));
        partialgameButton->setText(QApplication::translate("ChooserWindow", "Dor\303\241\305\276ka", nullptr));
        fullgameButton->setText(QApplication::translate("ChooserWindow", "Pln\303\241", nullptr));
        shutdownButton->setText(QApplication::translate("ChooserWindow", "Vypn\303\272\305\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooserWindow: public Ui_ChooserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSERWINDOW_H

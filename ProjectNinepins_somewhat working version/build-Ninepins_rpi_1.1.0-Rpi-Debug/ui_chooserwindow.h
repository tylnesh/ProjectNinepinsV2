/********************************************************************************
** Form generated from reading UI file 'chooserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSERWINDOW_H
#define UI_CHOOSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooserWindow
{
public:
    QPushButton *treningButton;
    QPushButton *dorazkaButton;
    QPushButton *plnaButton;
    QPushButton *pushButton;

    void setupUi(QDialog *ChooserWindow)
    {
        if (ChooserWindow->objectName().isEmpty())
            ChooserWindow->setObjectName(QStringLiteral("ChooserWindow"));
        ChooserWindow->resize(1024, 600);
        treningButton = new QPushButton(ChooserWindow);
        treningButton->setObjectName(QStringLiteral("treningButton"));
        treningButton->setEnabled(false);
        treningButton->setGeometry(QRect(110, 350, 300, 180));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(40);
        font.setBold(false);
        font.setWeight(50);
        treningButton->setFont(font);
        dorazkaButton = new QPushButton(ChooserWindow);
        dorazkaButton->setObjectName(QStringLiteral("dorazkaButton"));
        dorazkaButton->setGeometry(QRect(630, 80, 300, 180));
        dorazkaButton->setFont(font);
        plnaButton = new QPushButton(ChooserWindow);
        plnaButton->setObjectName(QStringLiteral("plnaButton"));
        plnaButton->setGeometry(QRect(110, 80, 300, 180));
        plnaButton->setFont(font);
        pushButton = new QPushButton(ChooserWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(630, 350, 300, 180));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush2(QColor(161, 161, 161, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        pushButton->setPalette(palette);
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setPointSize(40);
        pushButton->setFont(font1);
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);

        retranslateUi(ChooserWindow);

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(ChooserWindow);
    } // setupUi

    void retranslateUi(QDialog *ChooserWindow)
    {
        ChooserWindow->setWindowTitle(QApplication::translate("ChooserWindow", "Dialog", 0));
        treningButton->setText(QApplication::translate("ChooserWindow", "Tr\303\251ning", 0));
        dorazkaButton->setText(QApplication::translate("ChooserWindow", "Dor\303\241\305\276ka", 0));
        plnaButton->setText(QApplication::translate("ChooserWindow", "Pln\303\241", 0));
        pushButton->setText(QApplication::translate("ChooserWindow", "Vypn\303\272\305\245", 0));
    } // retranslateUi

};

namespace Ui {
    class ChooserWindow: public Ui_ChooserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSERWINDOW_H

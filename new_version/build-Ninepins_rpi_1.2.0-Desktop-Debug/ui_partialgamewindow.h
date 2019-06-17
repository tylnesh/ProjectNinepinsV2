/********************************************************************************
** Form generated from reading UI file 'partialgamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTIALGAMEWINDOW_H
#define UI_PARTIALGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PartialGameWindow
{
public:
    QPushButton *pin1;
    QPushButton *pin8;
    QPushButton *pin7;
    QPushButton *pin4;
    QPushButton *pin3;
    QLabel *label_3;
    QPushButton *pin5;
    QPushButton *pin0;
    QPushButton *pin6;
    QLabel *label_4;
    QLCDNumber *roundsLCD;
    QLCDNumber *scoreLCD;
    QPushButton *pin2;
    QLCDNumber *pointsLCD;
    QPushButton *changeStateButton;
    QPushButton *settingPinsButton;
    QPushButton *endGameButton;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *PartialGameWindow)
    {
        if (PartialGameWindow->objectName().isEmpty())
            PartialGameWindow->setObjectName(QString::fromUtf8("PartialGameWindow"));
        PartialGameWindow->resize(1024, 600);
        pin1 = new QPushButton(PartialGameWindow);
        pin1->setObjectName(QString::fromUtf8("pin1"));
        pin1->setGeometry(QRect(610, 310, 51, 171));
        pin1->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/kolok1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pin1->setIcon(icon);
        pin1->setIconSize(QSize(500, 110));
#ifndef QT_NO_SHORTCUT
        pin1->setShortcut(QString::fromUtf8(""));
#endif // QT_NO_SHORTCUT
        pin1->setCheckable(false);
        pin1->setAutoRepeat(false);
        pin1->setAutoExclusive(false);
        pin1->setAutoDefault(true);
        pin1->setFlat(true);
        pin8 = new QPushButton(PartialGameWindow);
        pin8->setObjectName(QString::fromUtf8("pin8"));
        pin8->setGeometry(QRect(710, 0, 53, 171));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/kolok1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/images/kolok2.png"), QSize(), QIcon::Normal, QIcon::On);
        pin8->setIcon(icon1);
        pin8->setIconSize(QSize(500, 110));
        pin8->setFlat(true);
        pin7 = new QPushButton(PartialGameWindow);
        pin7->setObjectName(QString::fromUtf8("pin7"));
        pin7->setGeometry(QRect(800, 110, 51, 171));
        pin7->setIcon(icon1);
        pin7->setIconSize(QSize(500, 110));
        pin7->setFlat(true);
        pin4 = new QPushButton(PartialGameWindow);
        pin4->setObjectName(QString::fromUtf8("pin4"));
        pin4->setGeometry(QRect(710, 200, 51, 171));
        pin4->setIcon(icon1);
        pin4->setIconSize(QSize(500, 110));
        pin4->setFlat(true);
        pin3 = new QPushButton(PartialGameWindow);
        pin3->setObjectName(QString::fromUtf8("pin3"));
        pin3->setGeometry(QRect(500, 200, 51, 171));
        pin3->setIcon(icon1);
        pin3->setIconSize(QSize(500, 110));
        pin3->setFlat(true);
        label_3 = new QLabel(PartialGameWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(810, 450, 211, 37));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(22);
        label_3->setFont(font);
        label_3->setAcceptDrops(false);
        label_3->setLayoutDirection(Qt::RightToLeft);
        pin5 = new QPushButton(PartialGameWindow);
        pin5->setObjectName(QString::fromUtf8("pin5"));
        pin5->setGeometry(QRect(910, 200, 51, 171));
        pin5->setIcon(icon1);
        pin5->setIconSize(QSize(500, 110));
        pin5->setFlat(true);
        pin0 = new QPushButton(PartialGameWindow);
        pin0->setObjectName(QString::fromUtf8("pin0"));
        pin0->setGeometry(QRect(710, 400, 51, 171));
        pin0->setIcon(icon1);
        pin0->setIconSize(QSize(500, 110));
        pin0->setFlat(true);
        pin6 = new QPushButton(PartialGameWindow);
        pin6->setObjectName(QString::fromUtf8("pin6"));
        pin6->setGeometry(QRect(610, 110, 51, 171));
        pin6->setIcon(icon1);
        pin6->setIconSize(QSize(500, 110));
        pin6->setFlat(true);
        label_4 = new QLabel(PartialGameWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 420, 191, 37));
        label_4->setFont(font);
        label_4->setAcceptDrops(false);
        label_4->setLayoutDirection(Qt::RightToLeft);
        roundsLCD = new QLCDNumber(PartialGameWindow);
        roundsLCD->setObjectName(QString::fromUtf8("roundsLCD"));
        roundsLCD->setGeometry(QRect(10, 470, 241, 101));
        scoreLCD = new QLCDNumber(PartialGameWindow);
        scoreLCD->setObjectName(QString::fromUtf8("scoreLCD"));
        scoreLCD->setGeometry(QRect(770, 490, 241, 101));
        pin2 = new QPushButton(PartialGameWindow);
        pin2->setObjectName(QString::fromUtf8("pin2"));
        pin2->setGeometry(QRect(800, 310, 51, 171));
        pin2->setIcon(icon1);
        pin2->setIconSize(QSize(500, 110));
        pin2->setFlat(true);
        pointsLCD = new QLCDNumber(PartialGameWindow);
        pointsLCD->setObjectName(QString::fromUtf8("pointsLCD"));
        pointsLCD->setGeometry(QRect(370, 470, 241, 101));
        changeStateButton = new QPushButton(PartialGameWindow);
        changeStateButton->setObjectName(QString::fromUtf8("changeStateButton"));
        changeStateButton->setGeometry(QRect(30, 130, 400, 100));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(22);
        font1.setBold(false);
        font1.setWeight(50);
        changeStateButton->setFont(font1);
        settingPinsButton = new QPushButton(PartialGameWindow);
        settingPinsButton->setObjectName(QString::fromUtf8("settingPinsButton"));
        settingPinsButton->setGeometry(QRect(30, 10, 400, 100));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Waree"));
        font2.setPointSize(22);
        settingPinsButton->setFont(font2);
        endGameButton = new QPushButton(PartialGameWindow);
        endGameButton->setObjectName(QString::fromUtf8("endGameButton"));
        endGameButton->setGeometry(QRect(30, 250, 400, 100));
        endGameButton->setFont(font);
        endGameButton->setIconSize(QSize(20, 16));
        endGameButton->setAutoExclusive(false);
        label_6 = new QLabel(PartialGameWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(370, 420, 191, 37));
        label_6->setFont(font);
        label_6->setAcceptDrops(false);
        label_6->setLayoutDirection(Qt::RightToLeft);
        label_7 = new QLabel(PartialGameWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(820, 20, 191, 37));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Verdana"));
        font3.setPointSize(26);
        font3.setBold(true);
        font3.setWeight(75);
        label_7->setFont(font3);
        label_7->setAcceptDrops(false);
        label_7->setLayoutDirection(Qt::RightToLeft);

        retranslateUi(PartialGameWindow);

        pin1->setDefault(false);
        settingPinsButton->setDefault(true);


        QMetaObject::connectSlotsByName(PartialGameWindow);
    } // setupUi

    void retranslateUi(QDialog *PartialGameWindow)
    {
        PartialGameWindow->setWindowTitle(QApplication::translate("PartialGameWindow", "Dialog", nullptr));
        pin1->setText(QString());
        pin8->setText(QString());
        pin7->setText(QString());
        pin4->setText(QString());
        pin3->setText(QString());
        label_3->setText(QApplication::translate("PartialGameWindow", "S\303\272\304\215et  kolkov", nullptr));
        pin5->setText(QString());
        pin0->setText(QString());
        pin6->setText(QString());
        label_4->setText(QApplication::translate("PartialGameWindow", "Po\304\215et hodov", nullptr));
        pin2->setText(QString());
        changeStateButton->setText(QApplication::translate("PartialGameWindow", "Upravi\305\245 stav", nullptr));
        settingPinsButton->setText(QApplication::translate("PartialGameWindow", "Stavanie", nullptr));
        endGameButton->setText(QApplication::translate("PartialGameWindow", "Koniec hry ", nullptr));
        label_6->setText(QApplication::translate("PartialGameWindow", "Zhodene", nullptr));
        label_7->setText(QApplication::translate("PartialGameWindow", "DORAZKA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PartialGameWindow: public Ui_PartialGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTIALGAMEWINDOW_H

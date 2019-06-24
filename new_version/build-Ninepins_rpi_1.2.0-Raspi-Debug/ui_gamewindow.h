/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QPushButton *pin4;
    QPushButton *pin3;
    QPushButton *pin0;
    QPushButton *pin5;
    QLCDNumber *roundsLCD;
    QLCDNumber *scoreLCD;
    QPushButton *settingPinsButton;
    QLabel *label_3;
    QLCDNumber *pointsLCD;
    QPushButton *pin6;
    QLabel *label_4;
    QPushButton *pin8;
    QPushButton *pin2;
    QPushButton *endGameButton;
    QPushButton *pin7;
    QPushButton *pin1;
    QPushButton *changeStateButton;
    QLabel *label_5;
    QLabel *label_7;

    void setupUi(QDialog *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->resize(1024, 600);
        pin4 = new QPushButton(GameWindow);
        pin4->setObjectName(QString::fromUtf8("pin4"));
        pin4->setEnabled(true);
        pin4->setGeometry(QRect(710, 200, 51, 171));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/kolok1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/kolok2.png"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QString::fromUtf8(":/images/kolok1.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/kolok2.png"), QSize(), QIcon::Disabled, QIcon::On);
        pin4->setIcon(icon);
        pin4->setIconSize(QSize(50, 110));
        pin4->setFlat(true);
        pin3 = new QPushButton(GameWindow);
        pin3->setObjectName(QString::fromUtf8("pin3"));
        pin3->setEnabled(true);
        pin3->setGeometry(QRect(500, 200, 51, 171));
        pin3->setMinimumSize(QSize(51, 0));
        pin3->setIcon(icon);
        pin3->setIconSize(QSize(50, 110));
        pin3->setFlat(true);
        pin0 = new QPushButton(GameWindow);
        pin0->setObjectName(QString::fromUtf8("pin0"));
        pin0->setEnabled(true);
        pin0->setGeometry(QRect(710, 400, 51, 171));
        pin0->setIcon(icon);
        pin0->setIconSize(QSize(50, 110));
        pin0->setFlat(true);
        pin5 = new QPushButton(GameWindow);
        pin5->setObjectName(QString::fromUtf8("pin5"));
        pin5->setEnabled(true);
        pin5->setGeometry(QRect(910, 200, 51, 171));
        pin5->setIcon(icon);
        pin5->setIconSize(QSize(50, 110));
        pin5->setFlat(true);
        roundsLCD = new QLCDNumber(GameWindow);
        roundsLCD->setObjectName(QString::fromUtf8("roundsLCD"));
        roundsLCD->setGeometry(QRect(10, 470, 241, 101));
        scoreLCD = new QLCDNumber(GameWindow);
        scoreLCD->setObjectName(QString::fromUtf8("scoreLCD"));
        scoreLCD->setGeometry(QRect(770, 490, 241, 101));
        settingPinsButton = new QPushButton(GameWindow);
        settingPinsButton->setObjectName(QString::fromUtf8("settingPinsButton"));
        settingPinsButton->setGeometry(QRect(30, 10, 400, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(22);
        font.setItalic(false);
        settingPinsButton->setFont(font);
        label_3 = new QLabel(GameWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(790, 450, 211, 37));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(22);
        label_3->setFont(font1);
        label_3->setAcceptDrops(false);
        label_3->setLayoutDirection(Qt::RightToLeft);
        pointsLCD = new QLCDNumber(GameWindow);
        pointsLCD->setObjectName(QString::fromUtf8("pointsLCD"));
        pointsLCD->setGeometry(QRect(280, 470, 241, 101));
        pin6 = new QPushButton(GameWindow);
        pin6->setObjectName(QString::fromUtf8("pin6"));
        pin6->setEnabled(true);
        pin6->setGeometry(QRect(610, 110, 51, 171));
        pin6->setIcon(icon);
        pin6->setIconSize(QSize(50, 110));
        pin6->setFlat(true);
        label_4 = new QLabel(GameWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 420, 191, 37));
        label_4->setFont(font1);
        label_4->setAcceptDrops(false);
        label_4->setLayoutDirection(Qt::RightToLeft);
        pin8 = new QPushButton(GameWindow);
        pin8->setObjectName(QString::fromUtf8("pin8"));
        pin8->setEnabled(true);
        pin8->setGeometry(QRect(710, 0, 53, 171));
        pin8->setIcon(icon);
        pin8->setIconSize(QSize(50, 110));
        pin8->setFlat(true);
        pin2 = new QPushButton(GameWindow);
        pin2->setObjectName(QString::fromUtf8("pin2"));
        pin2->setEnabled(true);
        pin2->setGeometry(QRect(800, 310, 51, 171));
        pin2->setIcon(icon);
        pin2->setIconSize(QSize(50, 110));
        pin2->setFlat(true);
        endGameButton = new QPushButton(GameWindow);
        endGameButton->setObjectName(QString::fromUtf8("endGameButton"));
        endGameButton->setGeometry(QRect(30, 250, 400, 100));
        endGameButton->setFont(font1);
        endGameButton->setIconSize(QSize(20, 16));
        endGameButton->setAutoExclusive(false);
        pin7 = new QPushButton(GameWindow);
        pin7->setObjectName(QString::fromUtf8("pin7"));
        pin7->setEnabled(true);
        pin7->setGeometry(QRect(800, 110, 51, 171));
        pin7->setIcon(icon);
        pin7->setIconSize(QSize(50, 110));
        pin7->setFlat(true);
        pin1 = new QPushButton(GameWindow);
        pin1->setObjectName(QString::fromUtf8("pin1"));
        pin1->setEnabled(true);
        pin1->setGeometry(QRect(610, 310, 61, 171));
        pin1->setMinimumSize(QSize(61, 0));
        pin1->setAutoFillBackground(false);
        pin1->setIcon(icon);
        pin1->setIconSize(QSize(50, 110));
#ifndef QT_NO_SHORTCUT
        pin1->setShortcut(QString::fromUtf8(""));
#endif // QT_NO_SHORTCUT
        pin1->setCheckable(false);
        pin1->setAutoRepeat(false);
        pin1->setAutoExclusive(false);
        pin1->setAutoDefault(true);
        pin1->setFlat(true);
        changeStateButton = new QPushButton(GameWindow);
        changeStateButton->setObjectName(QString::fromUtf8("changeStateButton"));
        changeStateButton->setGeometry(QRect(30, 130, 400, 100));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Verdana"));
        font2.setPointSize(22);
        font2.setBold(false);
        font2.setWeight(50);
        changeStateButton->setFont(font2);
        label_5 = new QLabel(GameWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 420, 191, 37));
        label_5->setFont(font1);
        label_5->setAcceptDrops(false);
        label_5->setLayoutDirection(Qt::RightToLeft);
        label_7 = new QLabel(GameWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(870, 20, 191, 37));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Verdana"));
        font3.setPointSize(26);
        font3.setBold(true);
        font3.setWeight(75);
        label_7->setFont(font3);
        label_7->setAcceptDrops(false);
        label_7->setLayoutDirection(Qt::RightToLeft);

        retranslateUi(GameWindow);

        settingPinsButton->setDefault(false);
        endGameButton->setDefault(true);
        pin1->setDefault(false);


        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QDialog *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Dialog", nullptr));
        pin4->setText(QString());
        pin3->setText(QString());
        pin0->setText(QString());
        pin5->setText(QString());
        settingPinsButton->setText(QApplication::translate("GameWindow", "Stavanie", nullptr));
        label_3->setText(QApplication::translate("GameWindow", "S\303\272\304\215et  kolkov", nullptr));
        pin6->setText(QString());
        label_4->setText(QApplication::translate("GameWindow", "Po\304\215et hodov", nullptr));
        pin8->setText(QString());
        pin2->setText(QString());
        endGameButton->setText(QApplication::translate("GameWindow", "Koniec hry ", nullptr));
        pin7->setText(QString());
        pin1->setText(QString());
        changeStateButton->setText(QApplication::translate("GameWindow", "Upravi\305\245 stav", nullptr));
        label_5->setText(QApplication::translate("GameWindow", "Zhodene", nullptr));
        label_7->setText(QApplication::translate("GameWindow", "PLNA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'partialgamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTIALGAMEWINDOW_H
#define UI_PARTIALGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PartialGameWindow
{
public:
    QPushButton *pin2;
    QPushButton *pin9;
    QPushButton *pin8;
    QPushButton *pin5;
    QPushButton *pin4;
    QLabel *label_3;
    QPushButton *pin6;
    QPushButton *pin1;
    QPushButton *pin7;
    QLabel *label_4;
    QLCDNumber *roundsLCD;
    QLCDNumber *scoreLCD;
    QPushButton *pin3;
    QLCDNumber *pointsLCD;
    QPushButton *stavButton;
    QPushButton *stavanieButton;
    QPushButton *koniecButton;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *PartialGameWindow)
    {
        if (PartialGameWindow->objectName().isEmpty())
            PartialGameWindow->setObjectName(QStringLiteral("PartialGameWindow"));
        PartialGameWindow->resize(1024, 600);
        pin2 = new QPushButton(PartialGameWindow);
        pin2->setObjectName(QStringLiteral("pin2"));
        pin2->setGeometry(QRect(610, 310, 51, 171));
        pin2->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/kolok1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pin2->setIcon(icon);
        pin2->setIconSize(QSize(500, 110));
        pin2->setShortcut(QStringLiteral(""));
        pin2->setCheckable(false);
        pin2->setAutoRepeat(false);
        pin2->setAutoExclusive(false);
        pin2->setAutoDefault(true);
        pin2->setFlat(true);
        pin9 = new QPushButton(PartialGameWindow);
        pin9->setObjectName(QStringLiteral("pin9"));
        pin9->setGeometry(QRect(710, 0, 53, 171));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/kolok1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/images/kolok2.png"), QSize(), QIcon::Normal, QIcon::On);
        pin9->setIcon(icon1);
        pin9->setIconSize(QSize(500, 110));
        pin9->setFlat(true);
        pin8 = new QPushButton(PartialGameWindow);
        pin8->setObjectName(QStringLiteral("pin8"));
        pin8->setGeometry(QRect(800, 110, 51, 171));
        pin8->setIcon(icon1);
        pin8->setIconSize(QSize(500, 110));
        pin8->setFlat(true);
        pin5 = new QPushButton(PartialGameWindow);
        pin5->setObjectName(QStringLiteral("pin5"));
        pin5->setGeometry(QRect(710, 200, 51, 171));
        pin5->setIcon(icon1);
        pin5->setIconSize(QSize(500, 110));
        pin5->setFlat(true);
        pin4 = new QPushButton(PartialGameWindow);
        pin4->setObjectName(QStringLiteral("pin4"));
        pin4->setGeometry(QRect(500, 200, 51, 171));
        pin4->setIcon(icon1);
        pin4->setIconSize(QSize(500, 110));
        pin4->setFlat(true);
        label_3 = new QLabel(PartialGameWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(810, 450, 211, 37));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(22);
        label_3->setFont(font);
        label_3->setAcceptDrops(false);
        label_3->setLayoutDirection(Qt::RightToLeft);
        pin6 = new QPushButton(PartialGameWindow);
        pin6->setObjectName(QStringLiteral("pin6"));
        pin6->setGeometry(QRect(910, 200, 51, 171));
        pin6->setIcon(icon1);
        pin6->setIconSize(QSize(500, 110));
        pin6->setFlat(true);
        pin1 = new QPushButton(PartialGameWindow);
        pin1->setObjectName(QStringLiteral("pin1"));
        pin1->setGeometry(QRect(710, 400, 51, 171));
        pin1->setIcon(icon1);
        pin1->setIconSize(QSize(500, 110));
        pin1->setFlat(true);
        pin7 = new QPushButton(PartialGameWindow);
        pin7->setObjectName(QStringLiteral("pin7"));
        pin7->setGeometry(QRect(610, 110, 51, 171));
        pin7->setIcon(icon1);
        pin7->setIconSize(QSize(500, 110));
        pin7->setFlat(true);
        label_4 = new QLabel(PartialGameWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 420, 191, 37));
        label_4->setFont(font);
        label_4->setAcceptDrops(false);
        label_4->setLayoutDirection(Qt::RightToLeft);
        roundsLCD = new QLCDNumber(PartialGameWindow);
        roundsLCD->setObjectName(QStringLiteral("roundsLCD"));
        roundsLCD->setGeometry(QRect(10, 470, 241, 101));
        scoreLCD = new QLCDNumber(PartialGameWindow);
        scoreLCD->setObjectName(QStringLiteral("scoreLCD"));
        scoreLCD->setGeometry(QRect(770, 490, 241, 101));
        pin3 = new QPushButton(PartialGameWindow);
        pin3->setObjectName(QStringLiteral("pin3"));
        pin3->setGeometry(QRect(800, 310, 51, 171));
        pin3->setIcon(icon1);
        pin3->setIconSize(QSize(500, 110));
        pin3->setFlat(true);
        pointsLCD = new QLCDNumber(PartialGameWindow);
        pointsLCD->setObjectName(QStringLiteral("pointsLCD"));
        pointsLCD->setGeometry(QRect(370, 470, 241, 101));
        stavButton = new QPushButton(PartialGameWindow);
        stavButton->setObjectName(QStringLiteral("stavButton"));
        stavButton->setGeometry(QRect(30, 130, 400, 100));
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setPointSize(22);
        font1.setBold(false);
        font1.setWeight(50);
        stavButton->setFont(font1);
        stavanieButton = new QPushButton(PartialGameWindow);
        stavanieButton->setObjectName(QStringLiteral("stavanieButton"));
        stavanieButton->setGeometry(QRect(30, 10, 400, 100));
        QFont font2;
        font2.setFamily(QStringLiteral("Waree"));
        font2.setPointSize(22);
        stavanieButton->setFont(font2);
        koniecButton = new QPushButton(PartialGameWindow);
        koniecButton->setObjectName(QStringLiteral("koniecButton"));
        koniecButton->setGeometry(QRect(30, 250, 400, 100));
        koniecButton->setFont(font);
        koniecButton->setIconSize(QSize(20, 16));
        koniecButton->setAutoExclusive(false);
        label_6 = new QLabel(PartialGameWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(370, 420, 191, 37));
        label_6->setFont(font);
        label_6->setAcceptDrops(false);
        label_6->setLayoutDirection(Qt::RightToLeft);
        label_7 = new QLabel(PartialGameWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(820, 20, 191, 37));
        QFont font3;
        font3.setFamily(QStringLiteral("Verdana"));
        font3.setPointSize(26);
        font3.setBold(true);
        font3.setWeight(75);
        label_7->setFont(font3);
        label_7->setAcceptDrops(false);
        label_7->setLayoutDirection(Qt::RightToLeft);

        retranslateUi(PartialGameWindow);

        pin2->setDefault(false);
        stavanieButton->setDefault(true);


        QMetaObject::connectSlotsByName(PartialGameWindow);
    } // setupUi

    void retranslateUi(QDialog *PartialGameWindow)
    {
        PartialGameWindow->setWindowTitle(QApplication::translate("PartialGameWindow", "Dialog", 0));
        pin2->setText(QString());
        pin9->setText(QString());
        pin8->setText(QString());
        pin5->setText(QString());
        pin4->setText(QString());
        label_3->setText(QApplication::translate("PartialGameWindow", "S\303\272\304\215et  kolkov", 0));
        pin6->setText(QString());
        pin1->setText(QString());
        pin7->setText(QString());
        label_4->setText(QApplication::translate("PartialGameWindow", "Po\304\215et hodov", 0));
        pin3->setText(QString());
        stavButton->setText(QApplication::translate("PartialGameWindow", "Upravi\305\245 stav", 0));
        stavanieButton->setText(QApplication::translate("PartialGameWindow", "Stavanie", 0));
        koniecButton->setText(QApplication::translate("PartialGameWindow", "Koniec hry ", 0));
        label_6->setText(QApplication::translate("PartialGameWindow", "Zhodene", 0));
        label_7->setText(QApplication::translate("PartialGameWindow", "DORAZKA", 0));
    } // retranslateUi

};

namespace Ui {
    class PartialGameWindow: public Ui_PartialGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTIALGAMEWINDOW_H

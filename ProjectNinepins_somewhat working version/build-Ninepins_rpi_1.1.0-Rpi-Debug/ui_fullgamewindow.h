/********************************************************************************
** Form generated from reading UI file 'fullgamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FULLGAMEWINDOW_H
#define UI_FULLGAMEWINDOW_H

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

class Ui_FullGameWindow
{
public:
    QPushButton *pin5;
    QPushButton *pin4;
    QPushButton *pin1;
    QPushButton *pin6;
    QLCDNumber *roundsLCD;
    QLCDNumber *scoreLCD;
    QPushButton *stavanieButton;
    QLabel *label_3;
    QLCDNumber *pointsLCD;
    QPushButton *pin7;
    QLabel *label_4;
    QPushButton *pin9;
    QPushButton *pin3;
    QPushButton *koniecButton;
    QPushButton *pin8;
    QPushButton *pin2;
    QPushButton *stavButton;
    QLabel *label_5;
    QLabel *label_7;

    void setupUi(QDialog *FullGameWindow)
    {
        if (FullGameWindow->objectName().isEmpty())
            FullGameWindow->setObjectName(QStringLiteral("FullGameWindow"));
        FullGameWindow->resize(1024, 600);
        pin5 = new QPushButton(FullGameWindow);
        pin5->setObjectName(QStringLiteral("pin5"));
        pin5->setEnabled(true);
        pin5->setGeometry(QRect(710, 200, 51, 171));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/kolok1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/kolok2.png"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QStringLiteral(":/images/kolok1.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/kolok2.png"), QSize(), QIcon::Disabled, QIcon::On);
        pin5->setIcon(icon);
        pin5->setIconSize(QSize(50, 110));
        pin5->setFlat(true);
        pin4 = new QPushButton(FullGameWindow);
        pin4->setObjectName(QStringLiteral("pin4"));
        pin4->setEnabled(true);
        pin4->setGeometry(QRect(500, 200, 51, 171));
        pin4->setMinimumSize(QSize(51, 0));
        pin4->setIcon(icon);
        pin4->setIconSize(QSize(50, 110));
        pin4->setFlat(true);
        pin1 = new QPushButton(FullGameWindow);
        pin1->setObjectName(QStringLiteral("pin1"));
        pin1->setEnabled(true);
        pin1->setGeometry(QRect(710, 400, 51, 171));
        pin1->setIcon(icon);
        pin1->setIconSize(QSize(50, 110));
        pin1->setFlat(true);
        pin6 = new QPushButton(FullGameWindow);
        pin6->setObjectName(QStringLiteral("pin6"));
        pin6->setEnabled(true);
        pin6->setGeometry(QRect(910, 200, 51, 171));
        pin6->setIcon(icon);
        pin6->setIconSize(QSize(50, 110));
        pin6->setFlat(true);
        roundsLCD = new QLCDNumber(FullGameWindow);
        roundsLCD->setObjectName(QStringLiteral("roundsLCD"));
        roundsLCD->setGeometry(QRect(10, 470, 241, 101));
        scoreLCD = new QLCDNumber(FullGameWindow);
        scoreLCD->setObjectName(QStringLiteral("scoreLCD"));
        scoreLCD->setGeometry(QRect(770, 490, 241, 101));
        stavanieButton = new QPushButton(FullGameWindow);
        stavanieButton->setObjectName(QStringLiteral("stavanieButton"));
        stavanieButton->setGeometry(QRect(30, 10, 400, 100));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(22);
        font.setItalic(false);
        stavanieButton->setFont(font);
        label_3 = new QLabel(FullGameWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(790, 450, 211, 37));
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setPointSize(22);
        label_3->setFont(font1);
        label_3->setAcceptDrops(false);
        label_3->setLayoutDirection(Qt::RightToLeft);
        pointsLCD = new QLCDNumber(FullGameWindow);
        pointsLCD->setObjectName(QStringLiteral("pointsLCD"));
        pointsLCD->setGeometry(QRect(280, 470, 241, 101));
        pin7 = new QPushButton(FullGameWindow);
        pin7->setObjectName(QStringLiteral("pin7"));
        pin7->setEnabled(true);
        pin7->setGeometry(QRect(610, 110, 51, 171));
        pin7->setIcon(icon);
        pin7->setIconSize(QSize(50, 110));
        pin7->setFlat(true);
        label_4 = new QLabel(FullGameWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 420, 191, 37));
        label_4->setFont(font1);
        label_4->setAcceptDrops(false);
        label_4->setLayoutDirection(Qt::RightToLeft);
        pin9 = new QPushButton(FullGameWindow);
        pin9->setObjectName(QStringLiteral("pin9"));
        pin9->setEnabled(true);
        pin9->setGeometry(QRect(710, 0, 53, 171));
        pin9->setIcon(icon);
        pin9->setIconSize(QSize(50, 110));
        pin9->setFlat(true);
        pin3 = new QPushButton(FullGameWindow);
        pin3->setObjectName(QStringLiteral("pin3"));
        pin3->setEnabled(true);
        pin3->setGeometry(QRect(800, 310, 51, 171));
        pin3->setIcon(icon);
        pin3->setIconSize(QSize(50, 110));
        pin3->setFlat(true);
        koniecButton = new QPushButton(FullGameWindow);
        koniecButton->setObjectName(QStringLiteral("koniecButton"));
        koniecButton->setGeometry(QRect(30, 250, 400, 100));
        koniecButton->setFont(font1);
        koniecButton->setIconSize(QSize(20, 16));
        koniecButton->setAutoExclusive(false);
        pin8 = new QPushButton(FullGameWindow);
        pin8->setObjectName(QStringLiteral("pin8"));
        pin8->setEnabled(true);
        pin8->setGeometry(QRect(800, 110, 51, 171));
        pin8->setIcon(icon);
        pin8->setIconSize(QSize(50, 110));
        pin8->setFlat(true);
        pin2 = new QPushButton(FullGameWindow);
        pin2->setObjectName(QStringLiteral("pin2"));
        pin2->setEnabled(true);
        pin2->setGeometry(QRect(610, 310, 61, 171));
        pin2->setMinimumSize(QSize(61, 0));
        pin2->setAutoFillBackground(false);
        pin2->setIcon(icon);
        pin2->setIconSize(QSize(50, 110));
        pin2->setShortcut(QStringLiteral(""));
        pin2->setCheckable(false);
        pin2->setAutoRepeat(false);
        pin2->setAutoExclusive(false);
        pin2->setAutoDefault(true);
        pin2->setFlat(true);
        stavButton = new QPushButton(FullGameWindow);
        stavButton->setObjectName(QStringLiteral("stavButton"));
        stavButton->setGeometry(QRect(30, 130, 400, 100));
        QFont font2;
        font2.setFamily(QStringLiteral("Verdana"));
        font2.setPointSize(22);
        font2.setBold(false);
        font2.setWeight(50);
        stavButton->setFont(font2);
        label_5 = new QLabel(FullGameWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(280, 420, 191, 37));
        label_5->setFont(font1);
        label_5->setAcceptDrops(false);
        label_5->setLayoutDirection(Qt::RightToLeft);
        label_7 = new QLabel(FullGameWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(870, 20, 191, 37));
        QFont font3;
        font3.setFamily(QStringLiteral("Verdana"));
        font3.setPointSize(26);
        font3.setBold(true);
        font3.setWeight(75);
        label_7->setFont(font3);
        label_7->setAcceptDrops(false);
        label_7->setLayoutDirection(Qt::RightToLeft);

        retranslateUi(FullGameWindow);

        stavanieButton->setDefault(false);
        koniecButton->setDefault(true);
        pin2->setDefault(false);


        QMetaObject::connectSlotsByName(FullGameWindow);
    } // setupUi

    void retranslateUi(QDialog *FullGameWindow)
    {
        FullGameWindow->setWindowTitle(QApplication::translate("FullGameWindow", "Dialog", 0));
        pin5->setText(QString());
        pin4->setText(QString());
        pin1->setText(QString());
        pin6->setText(QString());
        stavanieButton->setText(QApplication::translate("FullGameWindow", "Stavanie", 0));
        label_3->setText(QApplication::translate("FullGameWindow", "S\303\272\304\215et  kolkov", 0));
        pin7->setText(QString());
        label_4->setText(QApplication::translate("FullGameWindow", "Po\304\215et hodov", 0));
        pin9->setText(QString());
        pin3->setText(QString());
        koniecButton->setText(QApplication::translate("FullGameWindow", "Koniec hry ", 0));
        pin8->setText(QString());
        pin2->setText(QString());
        stavButton->setText(QApplication::translate("FullGameWindow", "Upravi\305\245 stav", 0));
        label_5->setText(QApplication::translate("FullGameWindow", "Zhodene", 0));
        label_7->setText(QApplication::translate("FullGameWindow", "PLNA", 0));
    } // retranslateUi

};

namespace Ui {
    class FullGameWindow: public Ui_FullGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FULLGAMEWINDOW_H

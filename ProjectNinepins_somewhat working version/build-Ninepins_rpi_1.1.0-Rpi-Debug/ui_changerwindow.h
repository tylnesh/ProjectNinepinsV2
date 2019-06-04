/********************************************************************************
** Form generated from reading UI file 'changerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGERWINDOW_H
#define UI_CHANGERWINDOW_H

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

class Ui_ChangerWindow
{
public:
    QPushButton *pin6;
    QPushButton *pin5;
    QLCDNumber *scoreLCD;
    QPushButton *pin7;
    QPushButton *pin2;
    QLCDNumber *roundsLCD;
    QLCDNumber *pointsLCD;
    QPushButton *pin4;
    QLabel *label_3;
    QPushButton *pin9;
    QLabel *label_4;
    QPushButton *pin3;
    QPushButton *pin1;
    QPushButton *pin8;
    QPushButton *scorePlus;
    QPushButton *scoreMinus;
    QPushButton *roundsPlus;
    QPushButton *roundsMinus;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *zeroButton;

    void setupUi(QDialog *ChangerWindow)
    {
        if (ChangerWindow->objectName().isEmpty())
            ChangerWindow->setObjectName(QStringLiteral("ChangerWindow"));
        ChangerWindow->resize(1024, 600);
        pin6 = new QPushButton(ChangerWindow);
        pin6->setObjectName(QStringLiteral("pin6"));
        pin6->setGeometry(QRect(930, 210, 100, 180));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/kolok1_big.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/kolok2_big.png"), QSize(), QIcon::Normal, QIcon::On);
        pin6->setIcon(icon);
        pin6->setIconSize(QSize(50, 110));
        pin6->setFlat(true);
        pin5 = new QPushButton(ChangerWindow);
        pin5->setObjectName(QStringLiteral("pin5"));
        pin5->setGeometry(QRect(650, 210, 100, 180));
        pin5->setIcon(icon);
        pin5->setIconSize(QSize(50, 110));
        pin5->setFlat(true);
        scoreLCD = new QLCDNumber(ChangerWindow);
        scoreLCD->setObjectName(QStringLiteral("scoreLCD"));
        scoreLCD->setGeometry(QRect(30, 450, 200, 131));
        pin7 = new QPushButton(ChangerWindow);
        pin7->setObjectName(QStringLiteral("pin7"));
        pin7->setGeometry(QRect(500, 90, 100, 180));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pin7->sizePolicy().hasHeightForWidth());
        pin7->setSizePolicy(sizePolicy);
        pin7->setIcon(icon);
        pin7->setIconSize(QSize(50, 110));
        pin7->setFlat(true);
        pin2 = new QPushButton(ChangerWindow);
        pin2->setObjectName(QStringLiteral("pin2"));
        pin2->setGeometry(QRect(500, 290, 100, 180));
        pin2->setAutoFillBackground(false);
        pin2->setIcon(icon);
        pin2->setIconSize(QSize(50, 110));
        pin2->setShortcut(QStringLiteral(""));
        pin2->setCheckable(false);
        pin2->setAutoRepeat(false);
        pin2->setAutoExclusive(false);
        pin2->setAutoDefault(true);
        pin2->setFlat(true);
        roundsLCD = new QLCDNumber(ChangerWindow);
        roundsLCD->setObjectName(QStringLiteral("roundsLCD"));
        roundsLCD->setGeometry(QRect(270, 450, 200, 131));
        pointsLCD = new QLCDNumber(ChangerWindow);
        pointsLCD->setObjectName(QStringLiteral("pointsLCD"));
        pointsLCD->setGeometry(QRect(800, 450, 200, 131));
        pin4 = new QPushButton(ChangerWindow);
        pin4->setObjectName(QStringLiteral("pin4"));
        pin4->setGeometry(QRect(370, 210, 100, 150));
        pin4->setIcon(icon);
        pin4->setIconSize(QSize(50, 110));
        pin4->setFlat(true);
        label_3 = new QLabel(ChangerWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 410, 211, 37));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(22);
        label_3->setFont(font);
        label_3->setAcceptDrops(false);
        label_3->setLayoutDirection(Qt::RightToLeft);
        pin9 = new QPushButton(ChangerWindow);
        pin9->setObjectName(QStringLiteral("pin9"));
        pin9->setGeometry(QRect(650, -30, 100, 180));
        pin9->setIcon(icon);
        pin9->setIconSize(QSize(50, 110));
        pin9->setFlat(true);
        label_4 = new QLabel(ChangerWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(280, 410, 201, 37));
        label_4->setFont(font);
        label_4->setAcceptDrops(false);
        label_4->setLayoutDirection(Qt::RightToLeft);
        pin3 = new QPushButton(ChangerWindow);
        pin3->setObjectName(QStringLiteral("pin3"));
        pin3->setGeometry(QRect(800, 290, 100, 180));
        pin3->setIcon(icon);
        pin3->setIconSize(QSize(50, 110));
        pin3->setFlat(true);
        pin1 = new QPushButton(ChangerWindow);
        pin1->setObjectName(QStringLiteral("pin1"));
        pin1->setGeometry(QRect(650, 450, 100, 180));
        pin1->setIcon(icon);
        pin1->setIconSize(QSize(50, 110));
        pin1->setAutoDefault(true);
        pin1->setFlat(true);
        pin8 = new QPushButton(ChangerWindow);
        pin8->setObjectName(QStringLiteral("pin8"));
        pin8->setGeometry(QRect(800, 90, 100, 180));
        pin8->setIcon(icon);
        pin8->setIconSize(QSize(50, 110));
        pin8->setFlat(true);
        scorePlus = new QPushButton(ChangerWindow);
        scorePlus->setObjectName(QStringLiteral("scorePlus"));
        scorePlus->setGeometry(QRect(80, 210, 90, 90));
        QFont font1;
        font1.setPointSize(30);
        scorePlus->setFont(font1);
        scoreMinus = new QPushButton(ChangerWindow);
        scoreMinus->setObjectName(QStringLiteral("scoreMinus"));
        scoreMinus->setGeometry(QRect(80, 320, 90, 90));
        scoreMinus->setFont(font1);
        roundsPlus = new QPushButton(ChangerWindow);
        roundsPlus->setObjectName(QStringLiteral("roundsPlus"));
        roundsPlus->setGeometry(QRect(250, 210, 90, 90));
        roundsPlus->setFont(font1);
        roundsMinus = new QPushButton(ChangerWindow);
        roundsMinus->setObjectName(QStringLiteral("roundsMinus"));
        roundsMinus->setGeometry(QRect(250, 320, 90, 90));
        roundsMinus->setFont(font1);
        okButton = new QPushButton(ChangerWindow);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(20, 10, 220, 80));
        QFont font2;
        font2.setPointSize(22);
        okButton->setFont(font2);
        cancelButton = new QPushButton(ChangerWindow);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(20, 110, 220, 80));
        cancelButton->setFont(font2);
        zeroButton = new QPushButton(ChangerWindow);
        zeroButton->setObjectName(QStringLiteral("zeroButton"));
        zeroButton->setEnabled(false);
        zeroButton->setGeometry(QRect(270, 10, 211, 81));
        zeroButton->setFont(font2);

        retranslateUi(ChangerWindow);

        pin2->setDefault(false);
        cancelButton->setDefault(true);


        QMetaObject::connectSlotsByName(ChangerWindow);
    } // setupUi

    void retranslateUi(QDialog *ChangerWindow)
    {
        ChangerWindow->setWindowTitle(QApplication::translate("ChangerWindow", "Dialog", 0));
        pin6->setText(QString());
        pin5->setText(QString());
        pin7->setText(QString());
        pin2->setText(QString());
        pin4->setText(QString());
        label_3->setText(QApplication::translate("ChangerWindow", "S\303\272\304\215et  kolkov", 0));
        pin9->setText(QString());
        label_4->setText(QApplication::translate("ChangerWindow", "Po\304\215et hodov", 0));
        pin3->setText(QString());
        pin1->setText(QString());
        pin8->setText(QString());
        scorePlus->setText(QApplication::translate("ChangerWindow", "+", 0));
        scoreMinus->setText(QApplication::translate("ChangerWindow", "-", 0));
        roundsPlus->setText(QApplication::translate("ChangerWindow", "+", 0));
        roundsMinus->setText(QApplication::translate("ChangerWindow", "-", 0));
        okButton->setText(QApplication::translate("ChangerWindow", "OK", 0));
        cancelButton->setText(QApplication::translate("ChangerWindow", "Zru\305\241i\305\245", 0));
        zeroButton->setText(QApplication::translate("ChangerWindow", "Vynuluj", 0));
    } // retranslateUi

};

namespace Ui {
    class ChangerWindow: public Ui_ChangerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGERWINDOW_H

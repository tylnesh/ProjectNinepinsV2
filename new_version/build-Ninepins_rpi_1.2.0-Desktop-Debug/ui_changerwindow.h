/********************************************************************************
** Form generated from reading UI file 'changerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGERWINDOW_H
#define UI_CHANGERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangerWindow
{
public:
    QPushButton *pin5;
    QPushButton *pin4;
    QLCDNumber *scoreLCD;
    QPushButton *pin6;
    QPushButton *pin1;
    QLCDNumber *roundsLCD;
    QLCDNumber *pointsLCD;
    QPushButton *pin3;
    QLabel *label_3;
    QPushButton *pin8;
    QLabel *label_4;
    QPushButton *pin2;
    QPushButton *pin0;
    QPushButton *pin7;
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
            ChangerWindow->setObjectName(QString::fromUtf8("ChangerWindow"));
        ChangerWindow->resize(1024, 600);
        pin5 = new QPushButton(ChangerWindow);
        pin5->setObjectName(QString::fromUtf8("pin5"));
        pin5->setGeometry(QRect(930, 210, 100, 180));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/kolok1_big.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/kolok2_big.png"), QSize(), QIcon::Normal, QIcon::On);
        pin5->setIcon(icon);
        pin5->setIconSize(QSize(50, 110));
        pin5->setFlat(true);
        pin4 = new QPushButton(ChangerWindow);
        pin4->setObjectName(QString::fromUtf8("pin4"));
        pin4->setGeometry(QRect(650, 210, 100, 180));
        pin4->setIcon(icon);
        pin4->setIconSize(QSize(50, 110));
        pin4->setFlat(true);
        scoreLCD = new QLCDNumber(ChangerWindow);
        scoreLCD->setObjectName(QString::fromUtf8("scoreLCD"));
        scoreLCD->setGeometry(QRect(30, 450, 200, 131));
        pin6 = new QPushButton(ChangerWindow);
        pin6->setObjectName(QString::fromUtf8("pin6"));
        pin6->setGeometry(QRect(500, 90, 100, 180));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pin6->sizePolicy().hasHeightForWidth());
        pin6->setSizePolicy(sizePolicy);
        pin6->setIcon(icon);
        pin6->setIconSize(QSize(50, 110));
        pin6->setFlat(true);
        pin1 = new QPushButton(ChangerWindow);
        pin1->setObjectName(QString::fromUtf8("pin1"));
        pin1->setGeometry(QRect(500, 290, 100, 180));
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
        roundsLCD = new QLCDNumber(ChangerWindow);
        roundsLCD->setObjectName(QString::fromUtf8("roundsLCD"));
        roundsLCD->setGeometry(QRect(270, 450, 200, 131));
        pointsLCD = new QLCDNumber(ChangerWindow);
        pointsLCD->setObjectName(QString::fromUtf8("pointsLCD"));
        pointsLCD->setGeometry(QRect(800, 450, 200, 131));
        pin3 = new QPushButton(ChangerWindow);
        pin3->setObjectName(QString::fromUtf8("pin3"));
        pin3->setGeometry(QRect(370, 210, 100, 150));
        pin3->setIcon(icon);
        pin3->setIconSize(QSize(50, 110));
        pin3->setFlat(true);
        label_3 = new QLabel(ChangerWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 410, 211, 37));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(22);
        label_3->setFont(font);
        label_3->setAcceptDrops(false);
        label_3->setLayoutDirection(Qt::RightToLeft);
        pin8 = new QPushButton(ChangerWindow);
        pin8->setObjectName(QString::fromUtf8("pin8"));
        pin8->setGeometry(QRect(650, -30, 100, 180));
        pin8->setIcon(icon);
        pin8->setIconSize(QSize(50, 110));
        pin8->setFlat(true);
        label_4 = new QLabel(ChangerWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(280, 410, 201, 37));
        label_4->setFont(font);
        label_4->setAcceptDrops(false);
        label_4->setLayoutDirection(Qt::RightToLeft);
        pin2 = new QPushButton(ChangerWindow);
        pin2->setObjectName(QString::fromUtf8("pin2"));
        pin2->setGeometry(QRect(800, 290, 100, 180));
        pin2->setIcon(icon);
        pin2->setIconSize(QSize(50, 110));
        pin2->setFlat(true);
        pin0 = new QPushButton(ChangerWindow);
        pin0->setObjectName(QString::fromUtf8("pin0"));
        pin0->setGeometry(QRect(650, 450, 100, 180));
        pin0->setIcon(icon);
        pin0->setIconSize(QSize(50, 110));
        pin0->setAutoDefault(true);
        pin0->setFlat(true);
        pin7 = new QPushButton(ChangerWindow);
        pin7->setObjectName(QString::fromUtf8("pin7"));
        pin7->setGeometry(QRect(800, 90, 100, 180));
        pin7->setIcon(icon);
        pin7->setIconSize(QSize(50, 110));
        pin7->setFlat(true);
        scorePlus = new QPushButton(ChangerWindow);
        scorePlus->setObjectName(QString::fromUtf8("scorePlus"));
        scorePlus->setGeometry(QRect(80, 210, 90, 90));
        QFont font1;
        font1.setPointSize(30);
        scorePlus->setFont(font1);
        scoreMinus = new QPushButton(ChangerWindow);
        scoreMinus->setObjectName(QString::fromUtf8("scoreMinus"));
        scoreMinus->setGeometry(QRect(80, 320, 90, 90));
        scoreMinus->setFont(font1);
        roundsPlus = new QPushButton(ChangerWindow);
        roundsPlus->setObjectName(QString::fromUtf8("roundsPlus"));
        roundsPlus->setGeometry(QRect(250, 210, 90, 90));
        roundsPlus->setFont(font1);
        roundsMinus = new QPushButton(ChangerWindow);
        roundsMinus->setObjectName(QString::fromUtf8("roundsMinus"));
        roundsMinus->setGeometry(QRect(250, 320, 90, 90));
        roundsMinus->setFont(font1);
        okButton = new QPushButton(ChangerWindow);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(20, 10, 220, 80));
        QFont font2;
        font2.setPointSize(22);
        okButton->setFont(font2);
        cancelButton = new QPushButton(ChangerWindow);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(20, 110, 220, 80));
        cancelButton->setFont(font2);
        zeroButton = new QPushButton(ChangerWindow);
        zeroButton->setObjectName(QString::fromUtf8("zeroButton"));
        zeroButton->setEnabled(false);
        zeroButton->setGeometry(QRect(270, 10, 211, 81));
        zeroButton->setFont(font2);

        retranslateUi(ChangerWindow);

        pin1->setDefault(false);
        cancelButton->setDefault(true);


        QMetaObject::connectSlotsByName(ChangerWindow);
    } // setupUi

    void retranslateUi(QDialog *ChangerWindow)
    {
        ChangerWindow->setWindowTitle(QApplication::translate("ChangerWindow", "Dialog", nullptr));
        pin5->setText(QString());
        pin4->setText(QString());
        pin6->setText(QString());
        pin1->setText(QString());
        pin3->setText(QString());
        label_3->setText(QApplication::translate("ChangerWindow", "S\303\272\304\215et  kolkov", nullptr));
        pin8->setText(QString());
        label_4->setText(QApplication::translate("ChangerWindow", "Po\304\215et hodov", nullptr));
        pin2->setText(QString());
        pin0->setText(QString());
        pin7->setText(QString());
        scorePlus->setText(QApplication::translate("ChangerWindow", "+", nullptr));
        scoreMinus->setText(QApplication::translate("ChangerWindow", "-", nullptr));
        roundsPlus->setText(QApplication::translate("ChangerWindow", "+", nullptr));
        roundsMinus->setText(QApplication::translate("ChangerWindow", "-", nullptr));
        okButton->setText(QApplication::translate("ChangerWindow", "OK", nullptr));
        cancelButton->setText(QApplication::translate("ChangerWindow", "Zru\305\241i\305\245", nullptr));
        zeroButton->setText(QApplication::translate("ChangerWindow", "Vynuluj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangerWindow: public Ui_ChangerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGERWINDOW_H

#ifndef FULLGAMEWINDOW_H
#define FULLGAMEWINDOW_H

#include <QtWidgets/QDialog>
//#include "commthread.h"
#include <QSerialPort>
#include "global.h"
#include "changerwindow.h"
#include "gpioclass.h"
#include <QCoreApplication>
#include <qtconcurrentrun.h>
#include <QThread>
#include "buttonchecker.h"
#include <QTimer>


namespace Ui {
class FullGameWindow;
}

class FullGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FullGameWindow(QWidget *parent = 0);
    ~FullGameWindow();
    ButtonChecker *buttonThread;
    GPIOClass* gpio21;
    std::string inputstate;
    QSerialPort *serial;
    QByteArray  serial_readData;
    QTextStream m_standardOutput;
    QTimer      serialTimer;
    QTimer      *redrawGuiTimer;
    QString serialBuffer;
    QString strWire;
    QString strCmd;
    QString strRnd;
    QString strPins[9];


    void loadMsg();
    int getNumberFromQString(const QString &xString);
    void parseMsg();
    void sndMsg();
    void sndScore();




private slots:

    void on_pin1_clicked();

    void on_pin2_clicked();

    void on_pin3_clicked();

    void on_pin4_clicked();

    void on_pin5_clicked();

    void on_pin6_clicked();

    void on_pin7_clicked();

    void on_pin8_clicked();

    void on_pin0_clicked();

    void on_changeStateButton_clicked();

    void on_settingPinsButton_clicked();

    void on_endGameButton_clicked();

private:
    Ui::FullGameWindow *ui;

public slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);
    void onRedrawGUI();
    void onCheckGaffe();


};

#endif // FULLGAMEWINDOW_H

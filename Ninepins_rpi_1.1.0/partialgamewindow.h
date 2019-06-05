#ifndef PARTIALGAMEWINDOW_H
#define PARTIALGAMEWINDOW_H

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
class PartialGameWindow;
}

class PartialGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PartialGameWindow(QWidget *parent = 0);
    ~PartialGameWindow();
    //CommThread *commThread;
    ButtonChecker *buttonThread;

    GPIOClass* gpio21;
     std::string inputstate;
    QSerialPort *serial;
    QByteArray  m_readData;
    QTextStream m_standardOutput;
    QTimer      m_timer;
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

    void on_pin9_clicked();

    void on_stavButton_clicked();

    void on_stavanieButton_clicked();

    void on_koniecButton_clicked();

private:
    Ui::PartialGameWindow *ui;

public slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);
    void onRedrawGUI();

};

#endif // PARTIALGAMEWINDOW_H

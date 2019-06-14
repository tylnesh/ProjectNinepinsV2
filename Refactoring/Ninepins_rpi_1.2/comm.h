#ifndef COMM_H
#define COMM_H
//#include <RF24/RF24.h>
//#define WIRE 450
#include "global.h"
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>



class Comm : public QObject
{
public:
    Comm();

    //communication

    /*void loadMsg(message msg);
    message saveMsg();*/

    void sndMsg();
    void rcvMsg();
    void loadMsg();

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serial;
    QByteArray  m_readData;
    QTextStream m_standardOutput;
    QTimer      m_timer;
    QString serialBuffer;
};

#endif // COMM_H

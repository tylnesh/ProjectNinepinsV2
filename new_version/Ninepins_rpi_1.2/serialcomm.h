#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>
#include "global.h"
#include <QDebug>


class SerialComm : public QObject
{
    Q_OBJECT
public:
    explicit SerialComm(QObject *parent = nullptr, QString path = "/dev/ttyUSB0", Status *msg = nullptr);
    ~SerialComm();
signals:

public slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);
    void onSendMsg(Status *msg);
    void onSendScore(Status *msg);


private:
    QSerialPort *serial;
    QByteArray  serialReadData;
    QTextStream m_standardOutput;
    QTimer      serialTimer;
    QString path;
    Status *msg;
    bool waitingForAck;
    bool requestedRepeat;




};

#endif // SERIALCOMM_H

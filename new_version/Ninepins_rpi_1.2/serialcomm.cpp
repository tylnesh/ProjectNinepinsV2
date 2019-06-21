#include "serialcomm.h"
#include <QDebug>

SerialComm::SerialComm(QObject *parent, QString path, Status *msg) : QObject(parent), path(path), msg(msg)
{

    serial = new QSerialPort();
    serial->setPortName(path);
    if (serial->open(QIODevice::ReadWrite))
    {
        serial->setBaudRate(QSerialPort::Baud57600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        connect(serial, &QSerialPort::readyRead, this, &SerialComm::handleReadyRead);
        connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &SerialComm::handleError);
        connect(&serialTimer, &QTimer::timeout, this, &SerialComm::handleTimeout);

        serialTimer.start(SERIALTIMER);


    } else qDebug() << "RS485 error msg: " << serial->errorString();

    //connect(parent, SIGNAL(sendMsg(&msg)), this, SLOT(onSendMsg(*msg)));


}




void SerialComm::handleReadyRead()
{
    serialReadData.append(serial->readAll());
    if (!serialTimer.isActive())
        serialTimer.start(SERIALTIMER);
}


void SerialComm::handleTimeout()
{
    if (serialReadData.isEmpty()) {
    } else {

        if (serialReadData.size() < statusLength)  return;
        Status *received = reinterpret_cast<Status*>(serialReadData.data());

        uint16_t tempChecksum =
                std::accumulate(received->bytes.begin(), received->bytes.end() - sizeof(Status::checksum), uint16_t(0));

        if (received->checksum == tempChecksum)
        {
            *msg = *received;
            switch(msg->cmd){
            case REQ_REPEAT:
                requestedRepeat = true;
                break;
            case ACKNOWLEDGED:
                waitingForAck = false;
                break;
            }
        }
        serialReadData = "";
    }



}

void SerialComm::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
          qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(serial->portName()).arg(serial->errorString()) << endl;
        //QCoreApplication::exit(1);
    }
}

void SerialComm::onSendMsg(Status *msg)
{

    msg->checksum = msg->calculateChecksum();
    qDebug() << "Sending msg...";
    qDebug() << "Wire: " << msg->wire;
    qDebug() << "Cmd: " << msg->cmd;
    qDebug() << "Pins: "; for (size_t i = 0; i < PINS; i++) qDebug() << msg->pins[i];
    qDebug() << "Rounds: " << msg->rounds;
    qDebug() << "Score: " << msg->score;
    qDebug() << "Checksum: " << msg->checksum;


    QByteArray serialMessage;
    for (size_t i = 0; i < sizeof(*msg); i++)
    {
        serialMessage.append(char(msg->bytes.at(i)));
    }

    serial->write(serialMessage);

    waitingForAck = true;
    requestedRepeat = false;

    if(waitingForAck)
    {
    if (requestedRepeat) onSendMsg(msg);
    }

}

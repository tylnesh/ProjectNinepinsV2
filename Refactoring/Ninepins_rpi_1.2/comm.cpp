/*
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "comm.h"
#include <RF24/RF24.h>
#include <unistd.h>
#include <iostream>
#include "global.h"
#include <QSerialPort>
#include <QDebug>
#include <string>
#include <sstream>

#define WIRE 150  // pairing the Arduino with RPI

using namespace std;

struct ardMsg
{

    int cmd=0;
    bool pins[9]={false,false,false,false,false,false,false,false,false};
    int wire = WIRE;
    int rounds=0;

};

ardMsg incoming;
ardMsg outgoing;
QSerialPort serial;



    //const uint64_t addresses[2] = { 0xABCDABCD71LL, 0x544d52687CLL };


    //RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);



Comm::Comm()
{


    serial = new QSerialPort();
    serialBuffer = "";
    serial->setPortName("/dev/ttyUSB0");
    if (serial->open(QIODevice::ReadWrite))
    {
        serial->setBaudRate(QSerialPort::Baud19200);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        qDebug()<< "Connection established";
        qDebug()<<serial->errorString();

        connect(serial, &QSerialPort::readyRead, this, &Comm::handleReadyRead);
        connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                    this, &Comm::handleError);
        connect(&m_timer, &QTimer::timeout, this, &Comm::handleTimeout);

            m_timer.start(2000);

    } else qDebug("False");


}



void Comm::sndMsg() {

    //serial.open();
    outgoing.cmd = cmdOutGF;
    outgoing.wire = WIRE;
    //radio.stopListening();
    printf("Sending message...\n");





}

void Comm::loadMsg() {
    outgoing.cmd = cmdOutGF;
    outgoing.wire = WIRE;
    outgoing.rounds = roundsOutGF;
    for (int i = 0; i< 9; i++) outgoing.pins[i] = pinsOutGF[i];
    }


void Comm::rcvMsg() {
    /*radio.startListening();
    //while (radio.available())
    {
        //radio.read(&incoming,sizeof(ardMsg));

std::cout<< "wire: " << incoming.wire << " cmd: " <<incoming.cmd << std::endl;

         if (incoming.wire == WIRE){
         if (incoming.cmd == 3){ardListening = true;} else if (incoming.cmd == 4) ardListening = false;
         else
         {

         std::cout<< "wire: " << incoming.wire << " cmd: " << incoming.cmd << std::endl;
         cmdGF = incoming.cmd;

         if (incoming.rounds != currentRound) {

             if (!isPartial) {

                 pointsGF = 0;
                 for (int i = 0; i<9; i++) {pinsGF[i] = incoming.pins[i]; if (pinsGF[i]) pointsGF++;}
                 roundsGF = currentRound;
                 scoreGF += pointsGF;
                 currentRound = incoming.rounds;
                 roundsGF = currentRound;
             }

             else {
                 pointsGF = 0;
                 for (int i = 0; i<9; i++) { pinsGF[i] = incoming.pins[i]; if (pinsGF[i]) pointsGF++;}
                 roundsGF = currentRound;

                 if (pointsGF == 9)
                 {scoreGF += pointsGF - lastPoints;  lastPoints = 0; pointsGF = 0;}
                 else {
                 scoreGF += pointsGF - lastPoints;
                 lastPoints  = pointsGF;
                 }
                 currentRound = incoming.rounds;
                 roundsGF = currentRound;

             }

         }
         else currentRound = incoming.rounds;

         }

 }}

*/ }

void Comm::handleReadyRead() {
    QStringList bufferSplit = serialBuffer.split(",");
    if (bufferSplit.length() < 13)
    {
        QByteArray serialData = serial->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
        // qDebug() << QString::fromStdString(serialData.toStdString());
    }else {
        qDebug() << bufferSplit; serialBuffer = "";
    }

    //qDebug() << m_readData;
    if (!m_timer.isActive())
        m_timer.start(5000);
}

void Comm::handleTimeout()
{
    if (m_readData.isEmpty()) {
        //qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serial->portName()) << endl;
    } else {
        //qDebug() << QObject::tr("Data successfully received from port %1").arg(serial->portName()) << endl;
        qDebug() << m_readData;

    }}

void Comm::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(serial->portName()).arg(serial->errorString()) << endl;
        //QCoreApplication::exit(1);
    }
}

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
#include "commthread.h"
#include <QtCore>

#include <iostream>
#include "fullgamewindow.h"
#include "gpioclass.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <QSerialPort>
#include <QtCore>
#define WIRE 150

GPIOClass* gpio21 = new GPIOClass("21"); //create new GPIO object to be attached to  GPIO21
string inputstate;

struct ardMsg
{

    int cmd=0;
    bool pins[9]={false,false,false,false,false,false,false,false,false};
    int wire = WIRE;
    int rounds=0;

};

ardMsg in;
ardMsg out;



#define RX true
#define TX false
#define QUIT 3



//Comm ct;

CommThread::CommThread(QObject *parent) :
    QThread(parent)
{
    serial= new QSerialPort();
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

    connect(serial, &QSerialPort::readyRead, this, &CommThread::handleReadyRead);
    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &CommThread::handleError);
    connect(&m_timer, &QTimer::timeout, this, &CommThread::handleTimeout);

        m_timer.start(2000);

} else qDebug("False");

//loadMsg();
//out.cmd = cmdOutGF;
//strWire = QString::fromStdString("w") + QString::number(out.wire);
//strCmd = QString::fromStdString("c") + QString::number(out.cmd);
//strRnd  = QString("r" + out.cmd);
//strWire = "w150";
//strCmd = "c24"    ;
//strRnd = "r15";
//qDebug()<< "Wire: " << strWire;
//qDebug()<< "CMD: " << strCmd;
//serial->write(strWire.toLatin1());
//serial->write(strCmd.toLatin1());




}

void CommThread::run()

{
    gpio21->export_gpio(); //export GPIO21
    gpio21->setdir_gpio("in");
    //int timer = 0;
    running = true;
    msleep(500);
    std::cout << "CommThread is running" <<std::endl;
    Stop = false;

    while (running)
    {
        //QMutex mutex;
       // mutex.lock();
        if(this->Stop) break;
        /*gpio21->getval_gpio(inputstate);
        if(inputstate == "0") // if input pin is at state "0" i.e. button pressed
                {
                    std::cout << "input pin state is Pressed. Will check input pin state again in 10ms "<<endl;
                        usleep(10000);
                            std::cout << "Checking again ....." << endl;
                            gpio21->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
                    if(inputstate == "0")
                    {
                        std::cout << "input pin state is definitely Pressed. " <<endl;

    faultSwitch = true;
    while (inputstate == "0"){
    gpio21->getval_gpio(inputstate);
    };

                    }
        }
*/

        //mutex.unlock();
        //msleep(10);
//timer++;
//if (timer > 500) { emit redrawGUI(); timer = 0;}

        switch (mode){
        case RX:
            //std::cout<<"RX mode"<<std::endl;

            break;

        case TX:
        qDebug()<<"TX mode";
            //if (changer) loadMsg();
            //for (int i = 0; i <3; i++)

            //strWire = "w150";
            //strCmd = "c24"    ;
            //strRnd = "r15";
            //out.cmd = cmdOutGF;
            //strWire = QString("w" + WIRE);
            //strCmd = QString("c" + out.cmd);
            //strRnd  = QString("r" + out.cmd);
            out.cmd = cmdOutGF;
            out.wire = WIRE;
            strWire = QString::fromStdString("w") + QString::number(out.wire);
            strCmd = QString::fromStdString("c") + QString::number(out.cmd);
            qDebug()<< strWire;
            qDebug()<< strCmd;
            serial->write(strWire.toLatin1());
            serial->write(strCmd.toLatin1());
            //serial->write(strRnd.toLatin1());


            mode = RX;

            break;

        default:
            break;
        }
            }


}





void CommThread::handleReadyRead()
{
/*
    //m_readData.append(serial->readAll());
QByteArray serialData =  serial->readAll();
serialBuffer += QString::fromStdString(serialData.toStdString());
qDebug() << serialBuffer;
*/
    QStringList bufferSplit = serialBuffer.split(",");
    if (bufferSplit.length() < 13)
    {
        QByteArray serialData = serial->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
        qDebug() << QString::fromStdString(serialData.toStdString());
    }else {
        qDebug() << bufferSplit;


        in.wire =  getNumberFromQString(bufferSplit[0]);
        qDebug() << "in wire: " << in.wire;
        in.cmd =  getNumberFromQString(bufferSplit[1]);
        qDebug() << "in cmd: " << in.cmd;

        for (int i =0; i<9; i++) {in.pins[i] = getNumberFromQString(bufferSplit[i+2]); qDebug() << "in pin"<< i << ": " << in.pins[i];}
        in.rounds = getNumberFromQString(bufferSplit[11]);
        qDebug() << "in rounds: " << in.rounds;
        //qDebug() << "in msg: " << bufferSplit[1];
        parseMsg();
        serialBuffer = "";
    }

    //qDebug() << m_readData;
    if (!m_timer.isActive())
        m_timer.start(5000);
}


void CommThread::handleTimeout()
{
    if (m_readData.isEmpty()) {
        //qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serial->portName()) << endl;
    } else {
        //qDebug() << QObject::tr("Data successfully received from port %1").arg(serial->portName()) << endl;
        //qDebug() << m_readData;

    }



}

void CommThread::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        //  qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(serial->portName()).arg(serial->errorString()) << endl;
        //QCoreApplication::exit(1);
    }
}

void CommThread::loadMsg(){
    out.cmd = cmdOutGF;
    out.wire = WIRE;
    out.rounds = roundsOutGF;
    for (int i = 0; i< 9; i++) out.pins[i] = pinsOutGF[i];
    }
/*

void sndMsg(){

    QString strWire = "w150";
    QString strCmd = "c24"    ;
    QString strRnd = "r15";
    serial->write(strWire.toLatin1());
    serial->write(strCmd.toLatin1());
    serial->write(strRnd.toLatin1());

}

void rcvMsg(){
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

}*/


int CommThread::getNumberFromQString(const QString &xString)
{
  QRegExp xRegExp("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");
  xRegExp.indexIn(xString);
  QStringList xList = xRegExp.capturedTexts();
  if (true == xList.empty())
  {
    return 0.0;
  }
  return xList.begin()->toInt();
}

void CommThread::parseMsg(){

    /*if (in.wire == WIRE){
             if (in.cmd == 3){ardListening = true;} else if (in.cmd == 4) ardListening = false;
             else
             {

             std::cout<< "wire: " << in.wire << " cmd: " << in.cmd << std::endl;
             cmdGF = in.cmd;

             if (in.rounds != currentRound) {

                 if (!isPartial) {

                     pointsGF = 0;
                     for (int i = 0; i<9; i++) {pinsGF[i] = in.pins[i]; if (pinsGF[i]) pointsGF++;}
                     roundsGF = currentRound;
                     scoreGF += pointsGF;
                     currentRound = in.rounds;
                     roundsGF = currentRound;
                 }

                 else {
                     pointsGF = 0;
                     for (int i = 0; i<9; i++) { pinsGF[i] = in.pins[i]; if (pinsGF[i]) pointsGF++;}
                     roundsGF = currentRound;

                     if (pointsGF == 9)
                     {scoreGF += pointsGF - lastPoints;  lastPoints = 0; pointsGF = 0;}
                     else {
                     scoreGF += pointsGF - lastPoints;
                     lastPoints  = pointsGF;
                     }
                     currentRound = in.rounds;
                     roundsGF = currentRound;

                 }

             }
             else currentRound = in.rounds;

             }

     }*/
    //if (in.wire == WIRE) {
    qDebug()<< in.wire;
    cmdGF = in.cmd;
    qDebug() << "CMDGF" << cmdGF;
    roundsGF = in.rounds;
    qDebug() << "ROUNDSGF" << roundsGF;
    for (int i = 0; i<9; i++) {pinsGF[i] = in.pins[i]; if (pinsGF[i]) pointsGF++; qDebug() << pinsGF[i];}
    scoreGF += pointsGF;
    emit redrawGUI();

    //}
}

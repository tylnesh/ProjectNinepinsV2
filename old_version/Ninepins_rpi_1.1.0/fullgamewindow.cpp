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
#include "fullgamewindow.h"
#include "ui_fullgamewindow.h"
#include <QtCore>
#include <iostream>
#include "global.h"
#include "fault.h"
#include "changerwindow.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "chooserwindow.h"
#include "delay.h"
#include <QSerialPort>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpioclass.h"
#include "buttonchecker.h"
#include <QCoreApplication>
#include <qtconcurrentrun.h>
#include <QThread>
#include <ctime>

#define WIRE 1
#define WIRE2 3


struct ardMsg
{

    int cmd=0;
    //bool pins[9]={false,false,false,false,false,false,false,false,false};
    int pins [9] = {0,0,0,0,0,0,0,0,0};
    int wire = WIRE;
    int rounds=0;
    int checksum = 0;

};

ardMsg F_incoming;
ardMsg F_outgoing;


using namespace std;


FullGameWindow::FullGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullGameWindow)
{
//    gpio21 = new GPIOClass("21"); //create new GPIO object to be attached to  GPIO21
//    gpio21->export_gpio(); //export GPIO21
//        gpio21->setdir_gpio("in");

//        QFuture<void> buttonChecker = QtConcurrent::run(&FullGameWindow::buttonCheck(), &gpio21);
//        buttonChecker.waitForFinished();

    isPartial = false;
    pointsGF = 0;
    scoreGF = 0;
    roundsGF = 0;
    ardListening = true;

    ui->setupUi(this);
    this ->setWindowFlags(Qt::Window);
    this ->showFullScreen();
    this ->setWindowTitle("FULL GAME");


    serial= new QSerialPort();
serial->setPortName("/dev/ttyUSB0");
if (serial->open(QIODevice::ReadWrite))
{
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    qDebug()<< "Connection established";
    qDebug()<<serial->errorString();

    buttonThread = new ButtonChecker(this);
    connect(buttonThread,SIGNAL(redrawGUI()),this,SLOT(onRedrawGUI()));
    buttonThread->start();

    connect(serial, &QSerialPort::readyRead, this, &FullGameWindow::handleReadyRead);
    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &FullGameWindow::handleError);
    connect(&m_timer, &QTimer::timeout, this, &FullGameWindow::handleTimeout);

        m_timer.start(2000);


} else qDebug("False");


cmdOutGF = 24;
sndMsg();

//QEventLoop loop;
//QTimer::singleShot(200, &loop, SLOT(quit())); loop.exec();
sndScore();

}

FullGameWindow::~FullGameWindow()
{
    buttonThread->Stop = true;
    while(buttonThread->isRunning()) {};
    serial->close();
    delete ui;
}

//redrawing pins icons || prekreslovanie ikoniek kolkov

void FullGameWindow::onRedrawGUI()
{
    if (faultSwitch && !faultRunning) {

        pointsTmp = pointsGF;
        scoreTmp = scoreGF;
        for (int i = 0; i<9; i++) pinsTmp[i] = pinsGF[i];

        fault f;
        cmdOutGF = 201;

        sndMsg();

        faultRunning = true;

            f.exec();
            while (faultRunning){}
            F_outgoing.cmd=cmdOutGF; sndMsg();
            //commThread->mode = false;

    }

    //if(ardListening) {
       // ui->plnahra->setIcon(QIcon(":/images/PlnaGreen.png"));
       // ui->stavanieButton->setEnabled(true);
        //ui->stavanieButton->setEnabled(true);
        //ui->stavButton->setEnabled(true);
    //}

    //else {
      //  ui->plnahra->setIcon(QIcon(":/images/PlnaRed.png"));
        //ui->stavanieButton->setDisabled(true);
        //ui->stavanieButton->setDisabled(true);
        //ui->stavButton->setDisabled(true);
  //  }

    ui->scoreLCD->display(scoreGF);
    ui->roundsLCD->display(roundsGF);
    ui->pointsLCD->display(pointsGF);

    if (!pinsGF[0]) ui->pin1->setIcon(QIcon(":/images/kolok1.png")); else ui->pin1->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[1]) ui->pin2->setIcon(QIcon(":/images/kolok1.png")); else ui->pin2->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[2]) ui->pin3->setIcon(QIcon(":/images/kolok1.png")); else ui->pin3->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[3]) ui->pin4->setIcon(QIcon(":/images/kolok1.png")); else ui->pin4->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[4]) ui->pin5->setIcon(QIcon(":/images/kolok1.png")); else ui->pin5->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[5]) ui->pin6->setIcon(QIcon(":/images/kolok1.png")); else ui->pin6->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[6]) ui->pin7->setIcon(QIcon(":/images/kolok1.png")); else ui->pin7->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[7]) ui->pin8->setIcon(QIcon(":/images/kolok1.png")); else ui->pin8->setIcon(QIcon(":/images/kolok2.png"));
    if (!pinsGF[8]) ui->pin9->setIcon(QIcon(":/images/kolok1.png")); else ui->pin9->setIcon(QIcon(":/images/kolok2.png"));
    //sndScore();



}

// controlling the pins via push buttons || ovladanie kolkov dotykovymi tlacitkami

void FullGameWindow::on_pin1_clicked()
{
   sndScore(); //if (pinsGF[0]) pinsGF[0] = false; else pinsGF[0] = true;
}

void FullGameWindow::on_pin2_clicked()
{
sndScore();   //if (pinsGF[1]) pinsGF[1] = false; else pinsGF[1] = true;
}

void FullGameWindow::on_pin3_clicked()
{
  sndScore(); // if (pinsGF[2]) pinsGF[2] = false; else pinsGF[2] = true;
}

void FullGameWindow::on_pin4_clicked()
{
  sndScore();  // if (pinsGF[3]) pinsGF[3] = false; else pinsGF[3] = true;
}

void FullGameWindow::on_pin5_clicked()
{
  sndScore(); // if (pinsGF[4]) pinsGF[4] = false; else pinsGF[4] = true;
}

void FullGameWindow::on_pin6_clicked()
{
   sndScore(); // if (pinsGF[5]) pinsGF[5] = false; else pinsGF[5] = true;
}

void FullGameWindow::on_pin7_clicked()
{
    sndScore(); //if (pinsGF[6]) pinsGF[6] = false; else pinsGF[6] = true;
}

void FullGameWindow::on_pin8_clicked()
{
    sndScore(); //if (pinsGF[7]) pinsGF[7] = false; else pinsGF[7] = true;
}

void FullGameWindow::on_pin9_clicked()
{
   sndScore(); //if (pinsGF[8]) pinsGF[8] = false; else pinsGF[8] = true;
}

void FullGameWindow::on_stavanieButton_clicked()
{

    QEventLoop loop;
    QTimer::singleShot(50, &loop, SLOT(quit()));
    loop.exec();
    cmdOutGF = 3;

    sndMsg();


   // qDebug() << "Stavanie msg: " << QString(msg);

}

void FullGameWindow::on_stavButton_clicked()
{
 cmdOutGF = 200;
 sndMsg();
 ChangerWindow ch;
 changerRunning = true;
 ch.exec();
 while (changerRunning) {}

 if (changer)
 {
     //cmdGF = cmdOutGF;
     //pointsGF = pointsOutGF;
     //roundsGF = roundsOutGF;
     //scoreGF = scoreOutGF;
     //for (int i = 0; i<9; i++) pinsGF[i] = pinsOutGF[i];
     sndMsg();
     onRedrawGUI();
     on_stavanieButton_clicked();
     sndScore();
 }
 else {
     QEventLoop loop;
     QTimer::singleShot(50, &loop, SLOT(quit()));
     loop.exec();
     sndMsg();}
}

void FullGameWindow::on_koniecButton_clicked()
{
    cmdOutGF = 100;

    sndMsg();

    buttonThread->Stop = true;

    currentRound = pointsGF = roundsGF = cmdGF = 0;

    for (int i = 0; i<9; i++) pinsGF[i] = 0;

    faultSwitch = false;

    Delay d;
    d.exec();

    close();
}




void FullGameWindow::handleReadyRead()
{



 m_readData.append(serial->readAll());
    if (!m_timer.isActive())
        m_timer.start(3000);
}


void FullGameWindow::handleTimeout()
{
    if (m_readData.isEmpty()) {
        //qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serial->portName()) << endl;
    } else {
        //qDebug() << QObject::tr("Data successfully received from port %1").arg(serial->portName()) << endl;
        qDebug() << m_readData;

        F_incoming.wire = QString(m_readData.mid(0,1)).toInt();


         //qDebug() <<  "m_readData[0]" <<  m_readData[0];
        qDebug() <<  "incoming wire" << F_incoming.wire;
        qDebug() << "QString(m_readData.mid(1,1)).toInt(): " << QString(m_readData.mid(1,1)).toInt();
        if (QString(m_readData.mid(1,1)).toInt() == 0)  F_incoming.cmd = QString(m_readData.mid(2,1)).toInt();
        else F_incoming.cmd = QString(m_readData.mid(1,2)).toInt();
        qDebug() <<  "incoming cmd" << F_incoming.cmd;
        for (int i = 0 ; i<9; i++) {
            F_incoming.pins[i] = QString(m_readData.mid(i+3,1)).toInt();
            qDebug() << "Pin: " << i << " " << F_incoming.pins[i];
        }
        if (QString(m_readData.mid(12,1)).toInt() == 0) F_incoming.rounds = QString(m_readData.mid(13,1)).toInt();
        else F_incoming.rounds = QString(m_readData.mid(12,2)).toInt();

        int checksum = 0;
        checksum += F_incoming.cmd + F_incoming.wire;
        for (int i = 0 ; i<9; i++) checksum += F_incoming.pins[i];
        checksum += F_incoming.rounds;

        qDebug() << "My checksum is: " << checksum;

        int inChecksum = 0;
        if (QString(m_readData.mid(14,1)).toInt() == 0) inChecksum = QString(m_readData.mid(15,1)).toInt();
        else inChecksum = QString(m_readData.mid(14,2)).toInt();

        qDebug() << "Incoming checksum is: " << inChecksum;

        if (checksum != inChecksum) { cmdOutGF = 6; sndMsg(); cmdOutGF = 1; }

        if (F_incoming.wire == WIRE && F_incoming.cmd == 1) { parseMsg(); sndScore();}
        if (F_incoming.wire == WIRE2 && F_incoming.cmd == 6) {sndScore();}

        //else if (F_incoming.cmd == 3 || F_incoming.cmd == 30  ) ardListening = true;
        //else if (F_incoming.cmd == 4 || F_incoming.cmd == 40 ) ardListening = false;

        //qDebug() << m_readData.toHex();
        m_readData = "";


    }



}

void FullGameWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        //  qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(serial->portName()).arg(serial->errorString()) << endl;
        //QCoreApplication::exit(1);
    }
}



void FullGameWindow::loadMsg(){
    F_outgoing.cmd = cmdOutGF;
    F_outgoing.wire = WIRE;
    F_outgoing.rounds = roundsOutGF;
    for (int i = 0; i< 9; i++) F_outgoing.pins[i] = pinsOutGF[i];
    }




int FullGameWindow::getNumberFromQString(const QString &xString)
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

void FullGameWindow::parseMsg(){

    //if (F_incoming.wire == WIRE){
             //if (F_incoming.cmd == 3){ardListening = true;} else if (F_incoming.cmd == 4) ardListening = false;
             //else
             {

             std::cout<< "wire: " << F_incoming.wire << " cmd: " << F_incoming.cmd << std::endl;
             cmdGF = F_incoming.cmd;

             if (F_incoming.rounds != currentRound) {

                 if (!isPartial) {

                     pointsGF = 0;
                     for (int i = 0; i<9; i++) {
                         pinsGF[i] = F_incoming.pins[i]; if (pinsGF[i]) pointsGF++;}
                     roundsGF = currentRound;
                     scoreGF += pointsGF;
                     currentRound = F_incoming.rounds;
                     roundsGF = currentRound;
                 }

                 else {
                     pointsGF = 0;
                     for (int i = 0; i<9; i++) {
                         pinsGF[i] = F_incoming.pins[i]; if (pinsGF[i]) pointsGF++;}
                     roundsGF = currentRound;

                     if (pointsGF == 9)
                     {scoreGF += pointsGF - lastPoints;  lastPoints = 0; //pointsGF = 0;
                     }
                     else {
                     scoreGF += pointsGF - lastPoints;
                     lastPoints  = pointsGF;
                     }
                     currentRound = F_incoming.rounds;
                     roundsGF = currentRound;

                 }

             }
             else currentRound = F_incoming.rounds;

             }

    // }
    /*//if (F_incoming.wire == WIRE) {
    qDebug()<< F_incoming.wire;
    cmdGF = F_incoming.cmd;
    qDebug() << "CMDGF" << cmdGF;
    roundsGF = F_incoming.rounds;
    qDebug() << "ROUNDSGF" << roundsGF;
    for (int i = 0; i<9; i++) {pinsGF[i] = F_incoming.pins[i]; if (pinsGF[i]) pointsGF++; qDebug() << pinsGF[i];}
    scoreGF += pointsGF;*/
    onRedrawGUI();

    //}
}


void FullGameWindow::sndMsg(){

    //QEventLoop loop;
    //QTimer::singleShot(50, &loop, SLOT(quit()));
   // loop.exec();


    F_outgoing.wire = WIRE;
    F_outgoing.cmd = cmdOutGF;
    if (cmdOutGF == 3) cmdOutGF = 1;
    for (int i = 0; i<9; i++) F_outgoing.pins[i] = pinsOutGF[i];
    F_outgoing.rounds = roundsOutGF;

    QByteArray w,c,r;
    QByteArray p[9];

    w.append(F_outgoing.wire);  c.append(F_outgoing.cmd);  r.append(F_outgoing.rounds);
    for (int i = 0; i<9; i++) p[i].append(F_outgoing.pins[i]);

    serial->write(w); serial->write(c);
    for (int i = 0; i<9; i++) serial->write(p[i]);
    serial->write(r);
//loop.exec();
}


void FullGameWindow::sndScore(){


    QEventLoop loop;
    QTimer::singleShot(50, &loop, SLOT(quit()));
    loop.exec();

    QByteArray w,r,p,s,c;


    w.append(3);  r.append(roundsGF);  p.append(pointsGF); s.append(scoreGF);
    c.append(3+roundsGF+pointsGF+scoreGF);

    serial->write(w); serial->write(r); serial->write(p); serial->write(s);
    serial->write(c);

   //loop.exec();
}


//void FullGameWindow::buttonCheck(GPIOClass gpio21) {

//    gpio21->getval_gpio(inputstate);
//            if(inputstate == "0") // if input pin is at state "0" i.e. button pressed
//                    {
//                        std::cout << "input pin state is Pressed. Will check input pin state again in 10ms "<<endl;
//                            usleep(10000);
//                                std::cout << "Checking again ....." << endl;
//                                gpio21->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
//                        if(inputstate == "0")
//                        {
//                            std::cout << "input pin state is definitely Pressed. " <<endl;

//        faultSwitch = true;
//        while (inputstate == "0"){
//        gpio21->getval_gpio(inputstate);
//        };
//                        }
//            }

//}

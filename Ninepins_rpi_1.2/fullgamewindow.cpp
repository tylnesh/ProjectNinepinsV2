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
#include "gaffe.h"
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



struct ardMsg
{

    int cmd = 0;
    int pins[9] = {0,0,0,0,0,0,0,0,0};
    int wire = DUEWIRE;
    int rounds = 0;
    int score = 0;
    int checksum = 0;

};

static ardMsg F_incoming;
static ardMsg F_outgoing;

using namespace std;


FullGameWindow::FullGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullGameWindow)
{
    isPartial = false;
    pointsGF = 0;
    scoreGF = 0;
    roundsGF = 0;

    ui->setupUi(this);
    this ->setWindowFlags(Qt::Window);
    this ->showFullScreen();
    this ->setWindowTitle("FULL GAME");

    //Timer redrawing the GUI every 500ms
    redrawGuiTimer = new QTimer(this);
    connect(redrawGuiTimer, SIGNAL(timeout()), this, SLOT(onRedrawGUI()));
    redrawGuiTimer->start(500);

    //Thread checking if the Big Red Gaffe Button is pressed
    buttonThread = new ButtonChecker(this);
    connect(buttonThread,SIGNAL(checkGaffe()),this,SLOT(onCheckGaffe()));
    //buttonThread->start();

    serial= new QSerialPort();
    serial->setPortName("/dev/ttyUSB0");
    if (serial->open(QIODevice::ReadWrite))
    {
        serial->setBaudRate(QSerialPort::Baud57600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        connect(serial, &QSerialPort::readyRead, this, &FullGameWindow::handleReadyRead);
        connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &FullGameWindow::handleError);
        connect(&serialTimer, &QTimer::timeout, this, &FullGameWindow::handleTimeout);

        serialTimer.start(SERIALTIMER);


    } else qDebug() << "RS485 error msg: " <<serial->errorString();

    cmdOutGF = FULLGAME;
    sndMsg();
    sndScore();

}

FullGameWindow::~FullGameWindow()
{
    buttonThread->Stop = true;
    while(buttonThread->isRunning()) {};
    serial->close();
    delete ui;
}

//redrawing GUI and checking if gaffe button was pressed
void FullGameWindow::onRedrawGUI()
{

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
}

void FullGameWindow::onCheckGaffe(){
    if (gaffeSwitch && !gaffeRunning) {

        pointsTmp = pointsGF;
        scoreTmp = scoreGF;
        for (int i = 0; i<9; i++) pinsTmp[i] = pinsGF[i];

        Gaffe f;
        cmdOutGF = 201;

        sndMsg();

        gaffeRunning = true;

        f.exec();
        while (gaffeRunning){}
        F_outgoing.cmd=cmdOutGF; sndMsg();
    }

}


void FullGameWindow::on_pin0_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin1_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin2_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin3_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin4_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin5_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin6_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin7_clicked()
{
    sndScore();
}

void FullGameWindow::on_pin8_clicked()
{
    sndScore();
}


void FullGameWindow::on_settingPinsButton_clicked()
{

    QEventLoop loop;
    QTimer::singleShot(50, &loop, SLOT(quit()));
    loop.exec();
    cmdOutGF = SETTINGPINS;

    sndMsg();


}

void FullGameWindow::on_changeStateButton_clicked()
{
    cmdOutGF = CHANGE;
    sndMsg();
    ChangerWindow ch;
    ch.exec();
    while (ch.isVisible()) {}

    if (changer)
    {
        sndMsg();
        sndScore();
        onRedrawGUI();
        on_settingPinsButton_clicked();

    }
    else {
        //again with the loop. I suspect I added it to make sure the message goes through
        //    QEventLoop loop;
        //    QTimer::singleShot(50, &loop, SLOT(quit()));
        //    loop.exec();
        sndMsg();
    }
}

void FullGameWindow::on_endGameButton_clicked()
{
    cmdOutGF = ENDGAME;
    sndMsg();

    //stopping the thread checking the Red Gaffe Button
    buttonThread->Stop = true;

    currentRound = pointsGF = roundsGF = cmdGF = 0;
    for (int i = 0; i<9; i++) pinsGF[i] = 0;
    gaffeSwitch = false;

    //delay allowing the pin setting mechanism to finish it's job, before BFUs start new game
    Delay d;
    d.exec();

    close();
}




void FullGameWindow::handleReadyRead()
{
    serial_readData.append(serial->readAll());
    if (!serialTimer.isActive())
        serialTimer.start(SERIALTIMER);
}


void FullGameWindow::handleTimeout()
{
    if (serial_readData.isEmpty()) {
    } else {
        //qDebug() << serial_readData;

        F_incoming.wire = QString(serial_readData.mid(0,1)).toInt();

        //reading cmd
        if (QString(serial_readData.mid(1,1)).toInt() == 0)  F_incoming.cmd = QString(serial_readData.mid(2,1)).toInt();
        else F_incoming.cmd = QString(serial_readData.mid(1,2)).toInt();

        //reading pins
        for (int i = 0 ; i<9; i++) {
            F_incoming.pins[i] = QString(serial_readData.mid(i+3,1)).toInt();
        }
        //reading rounds
        if (QString(serial_readData.mid(12,1)).toInt() == 0) F_incoming.rounds = QString(serial_readData.mid(13,1)).toInt();
        else F_incoming.rounds = QString(serial_readData.mid(12,2)).toInt();

        //reading score
        if (QString(serial_readData.mid(14,1)).toInt() == 0)
        {
            if(QString(serial_readData.mid(15,1)).toInt() == 0) F_incoming.score = QString(serial_readData.mid(16,1)).toInt();
            else {
                F_incoming.score = QString(serial_readData.mid(15,2)).toInt();
            }
        }
        else {
            F_incoming.score = QString(serial_readData.mid(14,3)).toInt();
        }

        //reading checksum
        if (QString(serial_readData.mid(17,1)).toInt() == 0)
        {
            if(QString(serial_readData.mid(18,1)).toInt() == 0) F_incoming.checksum = QString(serial_readData.mid(19,1)).toInt();
            else {
                F_incoming.checksum = QString(serial_readData.mid(18,2)).toInt();
            }
        }
        else {
            F_incoming.checksum = QString(serial_readData.mid(17,3)).toInt();
        }



          int checksum = 0 + F_incoming.wire +  F_incoming.cmd + F_incoming.rounds +F_incoming.score;
          for (int i = 0; i < 9; i++) checksum += F_incoming.pins[i];

          qDebug() << "Incoming checksum is: " << F_incoming.checksum;
          qDebug() << "Calculated checksum is: " << checksum;


        if (checksum != F_incoming.checksum) { cmdOutGF = CHECKSUMNOTMATCH; sndMsg(); cmdOutGF = FULLGAMEMSG; }

        if (F_incoming.wire == DUEWIRE && F_incoming.cmd == FULLGAMEMSG) { parseMsg(); sndScore();}
        if (F_incoming.wire == DISPLAYWIRE && F_incoming.cmd == CHECKSUMNOTMATCH) {sndScore();}


        serial_readData = "";


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
    F_outgoing.wire = DUEWIRE;
    F_outgoing.rounds = roundsOutGF;
    for (int i = 0; i < 9; i++) F_outgoing.pins[i] = pinsOutGF[i];
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

    {
        qDebug()<< "wire: " << F_incoming.wire << " cmd: " << F_incoming.cmd << endl;

        cmdGF = F_incoming.cmd;

        if (F_incoming.rounds != currentRound) {

            if (!isPartial) {

                pointsGF = 0;
                for (int i = 0; i < 9; i++) {
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


    onRedrawGUI();


}


void FullGameWindow::sndMsg(){

    F_outgoing.checksum = 0;
    F_outgoing.checksum += F_outgoing.wire = DUEWIRE;
    F_outgoing.checksum += F_outgoing.cmd = cmdOutGF;
    for (int i = 0; i < 9; i++) F_outgoing.checksum += F_outgoing.pins[i] = pinsOutGF[i];
    F_outgoing.checksum += F_outgoing.rounds = roundsOutGF;
    F_outgoing.checksum += F_outgoing.score = scoreOutGF;


    QByteArray wire,cmd,rounds,score,checksum;
    QByteArray pin[9];

    wire.append(F_outgoing.wire);
    cmd.append(F_outgoing.cmd);
    rounds.append(F_outgoing.rounds);
    for (int i = 0; i<9; i++) pin[i].append(F_outgoing.pins[i]);
    score.append(F_outgoing.score);
    checksum.append(F_outgoing.checksum);


    serial->write(wire);
    serial->write(cmd);
    for (int i = 0; i < 9; i++) serial->write(pin[i]);
    serial->write(rounds);
    serial->write(score);
    serial->write(checksum);

}


void FullGameWindow::sndScore(){

    // not sure why there's this timer loop... maybe just a delay from sending the message
    QEventLoop loop;
    QTimer::singleShot(50, &loop, SLOT(quit()));
    loop.exec();

    QByteArray wire,rounds,points,score,checksum;

    wire.append(DISPLAYWIRE);
    rounds.append(roundsGF);
    points.append(pointsGF);
    score.append(scoreGF);
    checksum.append(DISPLAYWIRE+roundsGF+pointsGF+scoreGF);

    serial->write(wire);
    serial->write(rounds);
    serial->write(points);
    serial->write(score);
    serial->write(checksum);

}



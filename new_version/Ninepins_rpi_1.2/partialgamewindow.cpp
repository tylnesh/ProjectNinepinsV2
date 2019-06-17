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
#include "partialgamewindow.h"
#include "ui_partialgamewindow.h"
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






PartialGameWindow::PartialGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PartialGameWindow)
{
    isPartial = false;
    scoreGF = 0;
    roundsGF = 0;
    currentGameType = Game::PARTIALGAME;

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
    buttonThread->start();

//    serial = new QSerialPort();
//    serial->setPortName("/dev/ttyUSB0");
//    if (serial->open(QIODevice::ReadWrite))
//    {
//        serial->setBaudRate(QSerialPort::Baud57600);
//        serial->setDataBits(QSerialPort::Data8);
//        serial->setParity(QSerialPort::NoParity);
//        serial->setStopBits(QSerialPort::OneStop);
//        serial->setFlowControl(QSerialPort::NoFlowControl);

//        connect(serial, &QSerialPort::readyRead, this, &PartialGameWindow::handleReadyRead);
//        connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
//                this, &PartialGameWindow::handleError);
//        connect(&serialTimer, &QTimer::timeout, this, &PartialGameWindow::handleTimeout);

//        serialTimer.start(SERIALTIMER);


//    } else qDebug() << "RS485 error msg: " << serial->errorString();

    state.cmd = FULLGAME;
    emit sendMsg(&state);
    //sndScore();

}

PartialGameWindow::~PartialGameWindow()
{
    buttonThread->stop = true;
    while(buttonThread->isRunning()) {};
    serial->close();
    delete ui;
}

//redrawing GUI and checking if gaffe button was pressed
void PartialGameWindow::onRedrawGUI()
{

    ui->scoreLCD->display(scoreGF);
    ui->roundsLCD->display(currentRound);
    ui->pointsLCD->display(state.getPoints());


    {
    if (!state.pins[0]) ui->pin0->setIcon(QIcon(":/images/kolok1.png")); else ui->pin0->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[1]) ui->pin1->setIcon(QIcon(":/images/kolok1.png")); else ui->pin1->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[2]) ui->pin2->setIcon(QIcon(":/images/kolok1.png")); else ui->pin2->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[3]) ui->pin3->setIcon(QIcon(":/images/kolok1.png")); else ui->pin3->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[4]) ui->pin4->setIcon(QIcon(":/images/kolok1.png")); else ui->pin4->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[5]) ui->pin5->setIcon(QIcon(":/images/kolok1.png")); else ui->pin5->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[6]) ui->pin6->setIcon(QIcon(":/images/kolok1.png")); else ui->pin6->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[7]) ui->pin7->setIcon(QIcon(":/images/kolok1.png")); else ui->pin7->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[8]) ui->pin8->setIcon(QIcon(":/images/kolok1.png")); else ui->pin8->setIcon(QIcon(":/images/kolok2.png"));
    }
}

void PartialGameWindow::onCheckGaffe(){
    if (gaffeSwitch && !gaffeRunning) {

        pointsTmp = state.getPoints();
        scoreTmp = scoreGF;
        for (size_t i = 0; i < PINS; i++) pinsTmp[i] = pinsGF[i];

        Gaffe gaffeWindow(this, &state);
        state.cmd = CHECKGAFFE;

        emit sendMsg(&state);
        gaffeRunning = true;

        gaffeWindow.exec();
        while (gaffeRunning){}
        emit sendMsg(&state);
    }

}


void PartialGameWindow::on_pin0_clicked()
{
    //sndScore();
}

void PartialGameWindow::on_pin1_clicked()
{
    //sndScore();
}

void PartialGameWindow::on_pin2_clicked()
{
//    sndScore();
}

void PartialGameWindow::on_pin3_clicked()
{
  //  sndScore();
}

void PartialGameWindow::on_pin4_clicked()
{
    //sndScore();
}

void PartialGameWindow::on_pin5_clicked()
{
    //sndScore();
}

void PartialGameWindow::on_pin6_clicked()
{
 //   sndScore();
}

void PartialGameWindow::on_pin7_clicked()
{
   // sndScore();
}

void PartialGameWindow::on_pin8_clicked()
{
 //   sndScore();
}


void PartialGameWindow::on_settingPinsButton_clicked()
{
    state.cmd = SETTINGPINS;
    emit sendMsg(&state);


}

void PartialGameWindow::on_changeStateButton_clicked()
{
    state.cmd = CHANGE;
    emit sendMsg(&state);
    ChangerWindow ch(this, &state);
    ch.exec();
    while (ch.isVisible()) {}

    if (changer)
    {
        emit sendMsg(&state);
        //sndScore();
        onRedrawGUI();
        on_settingPinsButton_clicked();

    }
    else {
        emit sendMsg(&state);
    }
}

void PartialGameWindow::on_endGameButton_clicked()
{
    state.cmd = ENDGAME;
    emit sendMsg(&state);

    //stopping the thread checking the Red Gaffe Button
    buttonThread->stop = true;

    currentRound = roundsGF = cmdGF = 0;
    for (size_t i = 0; i < PINS; i++) pinsGF[i] = 0;
    gaffeSwitch = false;

    //delay allowing the pin setting mechanism to finish it's job, before BFUs start new game
    Delay d;
    d.exec();

    close();
}



void PartialGameWindow::savePoints(){

    {

        if (currentRound != state.rounds)
        {
            if (currentGameType == Game::FULLGAME)  //  FULL GAME, count points, change rounds
            {
                state.score += state.getPoints();
                currentRound = state.rounds;
            } else                                  // PARTIAL GAME, save last rounds' in lastPoints.
            {
                if (state.getPoints() == PINS)
                {
                    state.score = state.getPoints() - lastPoints;
                    lastPoints = 0;
                } else
                {
                state.score += state.getPoints() - lastPoints;
                lastPoints = state.getPoints();
                }
               currentRound = state.rounds;
            }
        }
        else currentRound = state.rounds;
    }
}

//TODO: REMAKE THE COMMUNICATION INTO SEPARATE CLAAS


//void PartialGameWindow::sndScore(){

//    // not sure why there's this timer loop... maybe just a delay from sending the message
//    QEventLoop loop;
//    QTimer::singleShot(50, &loop, SLOT(quit()));
//    loop.exec();

//    QByteArray wire,rounds,points,score,checksum;

//    wire.append(DISPLAYWIRE);
//    rounds.append(roundsGF);
//    points.append(pointsGF);
//    score.append(scoreGF);
//    checksum.append(DISPLAYWIRE+roundsGF+pointsGF+scoreGF);

//    serial->write(wire);
//    serial->write(rounds);
//    serial->write(points);
//    serial->write(score);
//    serial->write(checksum);

//}



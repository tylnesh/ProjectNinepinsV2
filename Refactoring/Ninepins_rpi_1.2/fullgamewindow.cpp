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






FullGameWindow::FullGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullGameWindow)
{
    isPartial = false;
    scoreGF = 0;
    roundsGF = 0;
    currentGameType = Game::FULLGAME;

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

    serial = new QSerialPort();
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


    } else qDebug() << "RS485 error msg: " << serial->errorString();

    state.cmd = FULLGAME;
    sndMsg();
    sndScore();

}

FullGameWindow::~FullGameWindow()
{
    buttonThread->stop = true;
    while(buttonThread->isRunning()) {};
    serial->close();
    delete ui;
}

//redrawing GUI and checking if gaffe button was pressed
void FullGameWindow::onRedrawGUI()
{

    ui->scoreLCD->display(scoreGF);
    ui->roundsLCD->display(currentRound);
    ui->pointsLCD->display(state.getPoints());


    {
    if (!state.pins[0]) ui->pin1->setIcon(QIcon(":/images/kolok1.png")); else ui->pin1->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[1]) ui->pin2->setIcon(QIcon(":/images/kolok1.png")); else ui->pin2->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[2]) ui->pin3->setIcon(QIcon(":/images/kolok1.png")); else ui->pin3->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[3]) ui->pin4->setIcon(QIcon(":/images/kolok1.png")); else ui->pin4->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[4]) ui->pin5->setIcon(QIcon(":/images/kolok1.png")); else ui->pin5->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[5]) ui->pin6->setIcon(QIcon(":/images/kolok1.png")); else ui->pin6->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[6]) ui->pin7->setIcon(QIcon(":/images/kolok1.png")); else ui->pin7->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[7]) ui->pin8->setIcon(QIcon(":/images/kolok1.png")); else ui->pin8->setIcon(QIcon(":/images/kolok2.png"));
    if (!state.pins[8]) ui->pin9->setIcon(QIcon(":/images/kolok1.png")); else ui->pin9->setIcon(QIcon(":/images/kolok2.png"));
    }
}

void FullGameWindow::onCheckGaffe(){
    if (gaffeSwitch && !gaffeRunning) {

        pointsTmp = state.getPoints();
        scoreTmp = scoreGF;
        for (size_t i = 0; i < PINS; i++) pinsTmp[i] = pinsGF[i];

        Gaffe gaffeWindow(this, &state);
        state.cmd = CHECKGAFFE;

        sndMsg();
        gaffeRunning = true;

        gaffeWindow.exec();
        while (gaffeRunning){}
        sndMsg();
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
    state.cmd = SETTINGPINS;
    sndMsg();


}

void FullGameWindow::on_changeStateButton_clicked()
{
    state.cmd = CHANGE;
    sndMsg();
    ChangerWindow ch(this, &state);
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
        sndMsg();
    }
}

void FullGameWindow::on_endGameButton_clicked()
{
    state.cmd = ENDGAME;
    sndMsg();

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




void FullGameWindow::handleReadyRead()
{
    serialReadData.append(serial->readAll());
    if (!serialTimer.isActive())
        serialTimer.start(SERIALTIMER);
}


void FullGameWindow::handleTimeout()
{
    if (serialReadData.isEmpty()) {
    } else {

        if (serialReadData.size() < statusLength)  return;
        Status *received = reinterpret_cast<Status*>(serialReadData.data());

        uint16_t tempChecksum = std::accumulate(received->bytes.begin(), received->bytes.end() - sizeof(Status::checksum), uint16_t(0));
        if (received->checksum == tempChecksum) state = *received;


        serialReadData = "";


    }



}

void FullGameWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        //  qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(serial->portName()).arg(serial->errorString()) << endl;
        //QCoreApplication::exit(1);
    }
}


void FullGameWindow::savePoints(){

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


void FullGameWindow::sndMsg(){


    QByteArray serialMessage;
    for (size_t i = 0; i < sizeof(state); i++)
        serialMessage.append(char(state.bytes.at(i)));

    serial->write(serialMessage);

    while()




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



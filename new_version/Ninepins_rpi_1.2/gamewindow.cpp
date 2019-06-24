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
#include "gamewindow.h"
#include "ui_gamewindow.h"
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
#include "serialcomm.h"






GameWindow::GameWindow(QWidget *parent, Game currentGameType) :
    QDialog(parent),
    currentGameType(currentGameType),
    ui(new Ui::GameWindow)
{
    scoreGF = 0;
    roundsGF = 0;


    ui->setupUi(this);
    this ->setWindowFlags(Qt::Window);
    this ->showFullScreen();

    state.cmd = 0;
    state.wire = 0;
    state.score = 0;
    state.rounds = 0;
    for (uint8_t i = 0; i < PINS; i++) state.pins[i] = 0;
    state.checksum = 0;



    if (currentGameType == Game::FULL_GAME)
    {
        this ->setWindowTitle("PLNA");
        ui->label_7->setText("PLNA");
        state.wire = DUEWIRE;
        state.cmd = FULL_GAME;
    }else if(currentGameType == Game::PARTIAL_GAME)
    {
        this ->setWindowTitle("DORAZKA");
        ui->label_7->setText("DORAZKA");
        state.wire = DUEWIRE;
        state.cmd = PARTIAL_GAME;
    }


    //Timer redrawing the GUI every 500ms
    redrawGuiTimer = new QTimer(this);
    connect(redrawGuiTimer, SIGNAL(timeout()), this, SLOT(onRedrawGUI()));
    redrawGuiTimer->start(500);

    //Thread checking if the Big Red Gaffe Button is pressed
    buttonThread = new ButtonChecker(this);
    connect(buttonThread,SIGNAL(checkGaffe()),this,SLOT(onCheckGaffe()));
   // buttonThread->start();


     SerialComm *comm = new SerialComm(this, "/dev/ttyUSB0", &state);
    connect(this,SIGNAL(sendMsg(Status *)),comm,SLOT(onSendMsg(Status *)));

    emit sendMsg(&state);
    //sndScore();

}

GameWindow::~GameWindow()
{
    buttonThread->stop = true;
    while(buttonThread->isRunning()) {};
    serial->close();
    delete ui;
}

//redrawing GUI and checking if gaffe button was pressed
void GameWindow::onRedrawGUI()
{

    ui->scoreLCD->display(state.score);
    ui->roundsLCD->display(state.rounds);
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

void GameWindow::onCheckGaffe(){
    if (gaffeSwitch && !gaffeRunning) {

        pointsTmp = state.getPoints();
        scoreTmp = scoreGF;
        for (size_t i = 0; i < PINS; i++) pinsTmp[i] = pinsGF[i];

        Gaffe gaffeWindow(this, &state);
        state.cmd = CHECK_GAFFE;

        emit sendMsg(&state);
        gaffeRunning = true;

        gaffeWindow.exec();
        while (gaffeRunning){}
        emit sendMsg(&state);
    }

}


void GameWindow::on_pin0_clicked()
{
    //sndScore();
}

void GameWindow::on_pin1_clicked()
{
    //sndScore();
}

void GameWindow::on_pin2_clicked()
{
//    sndScore();
}

void GameWindow::on_pin3_clicked()
{
  //  sndScore();
}

void GameWindow::on_pin4_clicked()
{
    //sndScore();
}

void GameWindow::on_pin5_clicked()
{
    //sndScore();
}

void GameWindow::on_pin6_clicked()
{
 //   sndScore();
}

void GameWindow::on_pin7_clicked()
{
   // sndScore();
}

void GameWindow::on_pin8_clicked()
{
 //   sndScore();
}


void GameWindow::on_settingPinsButton_clicked()
{
    state.cmd = SETTING_PINS;
    emit sendMsg(&state);


}

void GameWindow::on_changeStateButton_clicked()
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

void GameWindow::on_endGameButton_clicked()
{
    state.cmd = END_GAME;
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



void GameWindow::savePoints(){

    {

        if (currentRound != state.rounds)
        {
            if (currentGameType == Game::FULL_GAME)  //  FULL GAME, count points, change rounds
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


//void FullGameWindow::sndScore(){

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



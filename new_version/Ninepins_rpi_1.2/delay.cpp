#include "delay.h"
#include "ui_delay.h"
#include "global.h"
#include <QTimer>

Delay::Delay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delay)
{
    ui->setupUi(this);
    this ->setWindowFlags(Qt::Window);
    this ->showFullScreen();
    ;
    if (currentGameType == Game::PARTIAL_GAME)
        QTimer::singleShot(13000,this,SLOT(onQuit())); // if the current game mode is "Partial Game", show the delay window for 13 seconds
    else QTimer::singleShot(2000,this,SLOT(onQuit()));  // otherwise just 2 seconds

}

Delay::~Delay()
{
    delete ui;
}


void Delay::onQuit()
{
    close();
}

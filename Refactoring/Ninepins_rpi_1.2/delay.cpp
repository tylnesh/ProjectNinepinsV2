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
    int countDown;
    if (isPartial) countDown=13; else countDown=2;
    QTimer::singleShot(countDown*1000,this,SLOT(onQuit()));
}

Delay::~Delay()
{
    delete ui;
}


void Delay::onQuit()
{
    close();
}

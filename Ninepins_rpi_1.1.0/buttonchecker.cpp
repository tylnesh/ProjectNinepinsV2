#include "buttonchecker.h"
#include "gpioclass.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <QtCore>
#include <QDebug>
GPIOClass* gpio21 = new GPIOClass("21"); //create new GPIO object to be attached to  GPIO21
string inputstate;

ButtonChecker::ButtonChecker(QObject *parent) :
    QThread(parent)
{

}

void ButtonChecker::run(){
    this->Stop= false;
    gpio21->export_gpio(); //export GPIO21
    gpio21->setdir_gpio("in");
    int timer = 0;
    running = true;
    msleep(500);
    qDebug() << "ButtonThread is running";

    while (running)
    {
        //QMutex mutex;
       // mutex.lock();
        if(this->Stop)  break;
        gpio21->getval_gpio(inputstate);
        if(inputstate == "0") // if input pin is at state "0" i.e. button pressed
                {
                    qDebug() << "input pin state is Pressed. Will check input pin state again in 10ms ";
                        usleep(10000);
                            qDebug() << "Checking again .....";
                            gpio21->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
                    if(inputstate == "0")
                    {
                        qDebug() << "input pin state is definitely Pressed. ";

    faultSwitch = true;
    while (inputstate == "0"){
    gpio21->getval_gpio(inputstate);
    };

                    }
        }


        //mutex.unlock();
        //msleep(10);
timer++;
if (timer > 500) { emit redrawGUI(); timer = 0;}


            }

}

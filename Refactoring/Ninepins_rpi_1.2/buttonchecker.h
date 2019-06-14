#ifndef BUTTONCHECKER_H
#define BUTTONCHECKER_H
#include "gpioclass.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <QThread>


class ButtonChecker: public QThread
{
    Q_OBJECT
public:
    explicit ButtonChecker(QObject *parent=nullptr);

    bool Stop;
    void run();
    bool running;


 signals:
     void checkGaffe();

 public slots:

private:
     GPIOClass* gpio21;
     string inputstate;

};

#endif // BUTTONCHECKER_H

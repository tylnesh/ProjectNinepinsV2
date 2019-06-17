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
    explicit ButtonChecker(QObject *parent=0);

    bool Stop;
    void run();
    bool running;


 signals:
     void redrawGUI();

 public slots:

};

#endif // BUTTONCHECKER_H

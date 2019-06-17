#ifndef COMMTHREAD_H
#define COMMTHREAD_H
#include <QThread>
//#define WIRE 450
//#include "comm.h"
#include "global.h"
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>


class CommThread: public QThread
{
    Q_OBJECT
public:
   explicit CommThread(QObject *parent = 0);
   //Comm cm;
   bool mode;


   QSerialPort *serial;
   QByteArray  m_readData;
   QTextStream m_standardOutput;
   QTimer      m_timer;
   QString serialBuffer;
   QString strWire;
   QString strCmd;
   QString strRnd;
   bool Stop;
   void run();
   bool running;
   //void sndMsg();
   //void rcvMsg();
   void loadMsg();
   int getNumberFromQString(const QString &xString);
   void parseMsg();


signals:
    void redrawGUI();
public slots:

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
};

#endif // COMMTHREAD_H

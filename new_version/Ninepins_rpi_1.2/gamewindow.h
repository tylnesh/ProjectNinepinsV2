#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets/QDialog>
//#include "commthread.h"
#include <QSerialPort>
#include "global.h"
#include "changerwindow.h"
#include "gpioclass.h"
#include <QCoreApplication>
#include <qtconcurrentrun.h>
#include <QThread>
#include "buttonchecker.h"
#include <QTimer>
#include "serialcomm.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, Game currentGameType = Game::FULL_GAME);
    ~GameWindow();
    ButtonChecker *buttonThread;
    GPIOClass* gpio21;
    std::string inputstate;
    QSerialPort *serial;
    QByteArray serialReadData;
    QTextStream m_standardOutput;
    QTimer serialTimer;
    QTimer *redrawGuiTimer;
    QString serialBuffer;
    QString strWire;
    QString strCmd;
    QString strRnd;
    QString strPins[PINS];

    void loadMsg();
    int getNumberFromQString(const QString &xString);
    void savePoints();

    //void sndScore();

signals:
    void sendMsg(Status *msg);
    void sendScore(Status *msg);




private slots:

    void on_pin1_clicked();

    void on_pin2_clicked();

    void on_pin3_clicked();

    void on_pin4_clicked();

    void on_pin5_clicked();

    void on_pin6_clicked();

    void on_pin7_clicked();

    void on_pin8_clicked();

    void on_pin0_clicked();

    void on_changeStateButton_clicked();

    void on_settingPinsButton_clicked();

    void on_endGameButton_clicked();

private:
    Game currentGameType;
    Ui::GameWindow *ui;
    SerialComm *comm;
    Status state;




public slots:

    void onRedrawGUI();
    void onCheckGaffe();


};

#endif // GAMEWINDOW_H

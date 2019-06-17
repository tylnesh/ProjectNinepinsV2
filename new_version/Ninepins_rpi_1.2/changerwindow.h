#ifndef CHANGERWINDOW_H
#define CHANGERWINDOW_H

#include <QtWidgets/QDialog>
#include "global.h"

namespace Ui {
class ChangerWindow;
}

class ChangerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangerWindow(QWidget *parent = nullptr, Status *msg = nullptr);
    ~ChangerWindow();

    void RedrawGUI();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_scorePlus_clicked();

    void on_scoreMinus_clicked();

    void on_roundsPlus_clicked();

    void on_roundsMinus_clicked();  

    void on_pin0_clicked();

    void on_pin1_clicked();

    void on_pin2_clicked();

    void on_pin3_clicked();

    void on_pin4_clicked();

    void on_pin5_clicked();

    void on_pin6_clicked();

    void on_pin7_clicked();

    void on_pin8_clicked();



    void on_zeroButton_clicked();

private:
    Status *msg;
    Ui::ChangerWindow *ui;
    int cmd = 0;
    int points = 0;
    int rounds = 0;
    int score = 0;
    bool pins[9] = {false, false, false, false, false, false, false, false, false};


    void switchPin(int i);

};

#endif // CHANGERWINDOW_H

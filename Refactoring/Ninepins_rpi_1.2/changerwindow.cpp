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

#include "changerwindow.h"
#include "ui_changerwindow.h"
#include "global.h"

ChangerWindow::ChangerWindow(QWidget *parent, Status *msg) :
    QDialog(parent),
    msg(msg),
    ui(new Ui::ChangerWindow)
{
    ui->setupUi(this);
    this ->setWindowFlags(Qt::Window);
    this ->showFullScreen();
    ui->zeroButton->setVisible(false);
    cmd = msg->cmd;
    points = msg->getPoints();
    rounds = msg->rounds;
    score = msg->score;
    for (size_t i = 0; i < 9; i++) pins[i] = msg->pins[i];
    RedrawGUI();

}

ChangerWindow::~ChangerWindow()
{
    delete ui;
}

void ChangerWindow::on_okButton_clicked()
{
    msg->cmd = CHANGEOK;
    msg->rounds = uint8_t(rounds);
    msg->score = uint16_t(score);
    for (size_t i = 0; i < 9; i++) msg->pins[i]= uint8_t(pins[i]);

    changer = true;
    close();
}

void ChangerWindow::on_cancelButton_clicked()
{
    msg->cmd = CHANGECANCEL;
    changer = false;
    close();
}

void ChangerWindow::on_scorePlus_clicked()
{
    score++;
    RedrawGUI();
}

void ChangerWindow::on_scoreMinus_clicked()
{
    score--;
    RedrawGUI();
}

void ChangerWindow::on_roundsPlus_clicked()
{
    rounds++;
    RedrawGUI();
}

void ChangerWindow::on_roundsMinus_clicked()
{
    rounds--;
    RedrawGUI();
}

void ChangerWindow::on_pin0_clicked()
{
    switchPin(0);
}

void ChangerWindow::on_pin1_clicked()
{  
    switchPin(1);
}

void ChangerWindow::on_pin2_clicked()
{
    switchPin(2);
}

void ChangerWindow::on_pin3_clicked()
{
    switchPin(3);

}

void ChangerWindow::on_pin4_clicked()
{
    switchPin(4);

}

void ChangerWindow::on_pin5_clicked()
{
    switchPin(5);
}

void ChangerWindow::on_pin6_clicked()
{
    switchPin(6);
}

void ChangerWindow::on_pin7_clicked()
{
    switchPin(7);

}

void ChangerWindow::on_pin8_clicked()
{
    switchPin(8);

}

void ChangerWindow::RedrawGUI()
{
    ui->scoreLCD->display(score);
    ui->roundsLCD->display(rounds);
    ui->pointsLCD->display(points);
{
    if (!pins[0]) ui->pin0->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin0->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[1]) ui->pin1->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin1->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[2]) ui->pin2->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin2->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[3]) ui->pin3->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin3->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[4]) ui->pin4->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin4->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[5]) ui->pin5->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin5->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[6]) ui->pin6->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin6->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[7]) ui->pin7->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin7->setIcon(QIcon(":/images/kolok2_big.png"));
    if (!pins[8]) ui->pin8->setIcon(QIcon(":/images/kolok1_big.png")); else ui->pin8->setIcon(QIcon(":/images/kolok2_big.png"));
}

}

//currently not visible, as users used to push it by mistake
void ChangerWindow::on_zeroButton_clicked()
{
    points = score = rounds = 0;
    RedrawGUI();
}


void ChangerWindow::switchPin(int i)
{
    if (pins[i])
    {
        pins[i] = false;
        points--; score--;
    }
        else
    {
        pins[i] = true;
        points++; score++;
    }
    RedrawGUI();
}

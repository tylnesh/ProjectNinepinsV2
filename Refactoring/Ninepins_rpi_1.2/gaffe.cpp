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
#include "gaffe.h"
#include "ui_gaffe.h"
#include "global.h"
#include "comm.h"



Gaffe::Gaffe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gaffe)
{
    ui->setupUi(this);
    this ->setWindowFlags(Qt::Window);
    this ->showFullScreen();
    gaffeRunning = true;

}

Gaffe::~Gaffe()
{
    delete ui;
}




void Gaffe::on_gaffeConfirmedButton_clicked()
{
    cmdOutGF = GAFFECONFIRMED;
    gaffeSwitch = false;
    gaffeConfirmed = true;
    gaffeRunning = false;

    pointsGF = pointsTmp;
    scoreGF = scoreTmp;
    for (int i = 0; i < 9; i++) pinsGF[i] = pinsTmp[i];

    close();
}

void Gaffe::on_gaffeCancelledButton_clicked()
{
    cmdOutGF = GAFFECANCELED;
    gaffeSwitch = false;
    gaffeConfirmed = false;
    gaffeRunning = false;
    close();
}

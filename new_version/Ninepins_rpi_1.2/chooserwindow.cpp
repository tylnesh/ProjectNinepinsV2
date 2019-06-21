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
#include "chooserwindow.h"
#include "ui_chooserwindow.h"
#include "gamewindow.h"
#include "global.h"
#include <iostream>
#include <stdlib.h>
#include <QTime>

ChooserWindow::ChooserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooserWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    //this->showFullScreen();
    
}

ChooserWindow::~ChooserWindow()
{
    delete ui;
}

void ChooserWindow::on_fullgameButton_clicked()
{

    GameWindow fg(this, Game::FULL_GAME);
    fg.exec();
}

void ChooserWindow::on_partialgameButton_clicked()
{

    GameWindow pg(this, Game::PARTIAL_GAME);
    pg.exec();
}

void ChooserWindow::on_shutdownButton_clicked()
{
    QCoreApplication::quit();
    system("shutdown -h now");
    close();
}

#include "isgreen.h"
#include "ui_isgreen.h"

IsGreen::IsGreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IsGreen)
{
    QDialog::connect(ui->yesButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    QDialog::connect(ui->noButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
            ui->setupUi(this);
}

IsGreen::~IsGreen()
{
    delete ui;
}

void IsGreen::on_noButton_clicked()
{

}

void IsGreen::on_yesButton_clicked()
{

}

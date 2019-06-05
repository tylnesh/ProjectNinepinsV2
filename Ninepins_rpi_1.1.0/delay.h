#ifndef DELAY_H
#define DELAY_H

#include <QtWidgets/QDialog>

namespace Ui {
class Delay;
}

class Delay : public QDialog
{
    Q_OBJECT

public:
    explicit Delay(QWidget *parent = 0);
    ~Delay();

private:
    Ui::Delay *ui;

public slots:
    void onQuit();
};

#endif // DELAY_H

#ifndef GAFFE_H
#define GAFFE_H

#include <QtWidgets/QDialog>

namespace Ui {
class gaffe;
}

class Gaffe : public QDialog
{
    Q_OBJECT

public:
    explicit Gaffe(QWidget *parent = nullptr);
    ~Gaffe();


private slots:

    void on_gaffeConfirmedButton_clicked();

    void on_gaffeCancelledButton_clicked();

private:
    Ui::gaffe *ui;
};

#endif // GAFFE_H

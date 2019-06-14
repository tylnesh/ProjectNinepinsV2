#ifndef ISGREEN_H
#define ISGREEN_H

#include <QDialog>

namespace Ui {
class IsGreen;
}

class IsGreen : public QDialog
{
    Q_OBJECT

public:
    explicit IsGreen(QWidget *parent = 0);
    ~IsGreen();

private slots:
    void on_noButton_clicked();

    void on_yesButton_clicked();

private:
    Ui::IsGreen *ui;
};

#endif // ISGREEN_H

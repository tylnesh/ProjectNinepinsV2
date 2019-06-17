#ifndef CHOOSERWINDOW_H
#define CHOOSERWINDOW_H

#include <QtWidgets/QDialog>
#include "global.h"
#include <QSerialPort>

namespace Ui {
class ChooserWindow;
}

class ChooserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooserWindow(QWidget *parent = nullptr);
    ~ChooserWindow();

private slots:
    void on_fullgameButton_clicked();
    
    void on_partialgameButton_clicked();

    void on_shutdownButton_clicked();

private:
    Ui::ChooserWindow *ui;

public slots:
};

#endif // CHOOSERWINDOW_H
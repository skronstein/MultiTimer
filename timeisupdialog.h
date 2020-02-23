#ifndef TIMEISUPDIALOG_H
#define TIMEISUPDIALOG_H

#include <QDialog>
#include "mywidget.h"

class MyWidget;

namespace Ui {
class TimeIsUpDialog;
}

class TimeIsUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeIsUpDialog(QWidget *parent = 0);
    ~TimeIsUpDialog();

private slots:
    void on_RestartNextDayButton_clicked();

    void on_EditTimerButton_clicked();

    void flashText();
private:
    QTimer timer;
    Ui::TimeIsUpDialog *ui;
    MyWidget *widgetPtr;
};

#endif // TIMEISUPDIALOG_H

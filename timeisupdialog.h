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

private:
    Ui::TimeIsUpDialog *ui;
    MyWidget *widgetPtr;
};

#endif // TIMEISUPDIALOG_H

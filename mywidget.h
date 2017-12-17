#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "edittimerwindow.h"
#include <QTime>
#include <QTimer>

class editTimerWindow;

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::MyWidget *ui;
    editTimerWindow *editWindow;
    int origTime;

public:
    explicit MyWidget(QWidget *parent = 0);
    QTimer updateTimer;
    short sDisplay;
    ~MyWidget();
    bool displayTimeInTitle, reminderBool, reminderBeforeDoneBool, reminderBeforeDoneShowedBool;
    int reminderBeforeMins, fontSize, updateTimerCounter, updateTimerInterval;
    int getFontSize();
    void setProgressBarVisibility(bool setting);
    QTime endTime;
    QString windowTitleOnly;
    editTimerWindow *editTimerPtr;

public slots:
    void setEndTime(QTime newEndTime);
    void setDuration(int hours, int mins);
    void setTextColor(QColor);
    void updateTimeDisplay();
    void setTextSize(int size);
    bool getProgressBarVisibility();
    void timeoutSlot();
    void adjustTextSize();

private slots:
    void on_EditButton_clicked();
    void checkIfTimeIsUp();

};

#endif // MYWIDGET_H

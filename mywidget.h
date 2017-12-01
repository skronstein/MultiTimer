#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "edittimerwindow.h"
#include <QTime>
#include <QTimer>

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
    bool finished;
    ~MyWidget();
    bool reminderBool, reminderBeforeDoneBool, reminderBeforeDoneShowedBool;
    int reminderBeforeMins, fontSize;
    int getFontSize();
    void setProgressBarVisibility(bool setting);
    QTime endTime;
    bool displayTimeInTitle;
    QString windowTitleOnly;

public slots:
    void setEndTime(QTime newEndTime);
    void setDuration(int hours, int mins);
    void setTextColor(QColor);
    void updateTimeDisplay();
    void setTextSize(int size);
    bool getProgressBarVisibility();

private slots:
    void on_EditButton_clicked();

};

#endif // MYWIDGET_H

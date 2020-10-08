#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "edittimerwindow.h"
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include "timeisupdialog.h"

class editTimerWindow;
class TimeIsUpDialog;

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::MyWidget *ui;
    TimeIsUpDialog  *TIUDialog;
    int origTime;

public:
    editTimerWindow *editTimerPtr;
    explicit MyWidget(QWidget *parent = 0);
    QTimer updateTimer;
    short sDisplay;
    ~MyWidget();
    bool displayTimeInTitle, reminderBool, reminderBeforeDoneBool, reminderBeforeDoneShowedBool;
    int reminderBeforeMins, fontSize, updateTimerCounter, updateTimerInterval;
    int getFontSize();
    void setProgressBarVisibility(bool setting);
    QDateTime endDateTime;
    QString windowTitleOnly;
	QMessageBox *messagebox = nullptr;

public slots:
    void setEndTime(QTime newEndTime);
    void setDuration(int hours, int mins);
    void setTextColor(QColor);
    void updateTimeDisplay();
    void setTextSize(int size);
    bool getProgressBarVisibility();
    void timeoutSlot();
    void adjustTextSize();
    void restartAfterFin();
    void restartAfterCurrentTime();
    void closeTimer();
    void minimizeTimer();

private slots:
    void on_EditButton_clicked();
    void checkIfTimeIsUp();
    void resizeEvent(QResizeEvent *event);
    void nullifyMessageboxPointer();
};

#endif // MYWIDGET_H

#include <QTime>
#include "childwindow.h"
#include "mywidget.h"
#include "ui_mywidget.h"
#include "edittimerwindow.h"
#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include <QProgressBar>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //default values
    setWindowTitle("New Timer");
    windowTitleOnly = windowTitle();
    updateTimer.setInterval(1);
    reminderBool = true;
    reminderBeforeDoneBool = true;
    reminderBeforeDoneShowedBool = false;
    reminderBeforeMins = 1;
    fontSize = 30;
    sDisplay = 0;
    ui->progressBar->setVisible(false);

    editTimerWindow *editTimer = new editTimerWindow(this);
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateTimeDisplay()));
    editTimer->setAttribute(Qt::WA_DeleteOnClose);
    editTimer->show();
}


void MyWidget::on_EditButton_clicked()
{
    editTimerWindow *editTimer = new editTimerWindow(this);
    editTimer->show();
}

void MyWidget::setEndTime(QTime newEndTime){
    if(endTime != newEndTime){
    endTime = newEndTime;
    origTime = QTime::currentTime().secsTo(endTime);
    }
}


void MyWidget::setDuration(int hours, int mins){
    QTime time = QTime::currentTime();

    mins += time.minute();
    hours += time.hour();

    if(mins >= 60){ //to prevent an invalid value of minutes being fed to the setHMS function below
        hours++;
        mins %= 60;
    }
    hours %= 24;


    if(time.isValid()) {
         endTime.setHMS(hours, mins, time.second(), 0);
         origTime = QTime::currentTime().secsTo(endTime);
    }
    else {
        qDebug() <<"time is not valid";
        QMessageBox::warning(this, "Invalid time error", "Invalid time error");
    }
}


void MyWidget::updateTimeDisplay(){
    int timeTo = QTime::currentTime().secsTo(endTime);
    int h, m;
    if(origTime != 0) ui->progressBar->setValue(100 - timeTo*100/origTime);

    h = timeTo / 3600;
    timeTo %= 3600;
    m = timeTo / 60;
    timeTo %= 60; //after this line, timeTo now represents the number of seconds to be displayed, not necessarily the number of seconds until the timer is up

    QString textToDisplay;

    //hours
    if(h != 0) textToDisplay.append(QString::number(h) + "h : ");

    //mins
    textToDisplay.append(QString::number(m) + "m");

    //seconds
    if(sDisplay > 0){
        if(sDisplay == 1 ) timeTo /= 10; //to remove the last digit of the number of seconds
        textToDisplay.append(" : " + QString::number(timeTo)+ "s");
    }

    ui->timeDisplay->setText(textToDisplay);

    if(((float)(QTime::currentTime().secsTo(endTime) / 60 ) < (reminderBeforeMins)) && !reminderBeforeDoneShowedBool){
        reminderBeforeDoneShowedBool = true;
        QMessageBox::information(this, QString::number(reminderBeforeMins) + " minutes until: " + windowTitle(),
                                       "Time is now " + QTime::currentTime().toString());
    }

    if(QTime::currentTime().secsTo(endTime) <= 0){
        updateTimer.stop();
        if(reminderBool) QMessageBox::information(this, "Time for: " + windowTitle(),
                                                        "Time is now " + QTime::currentTime().toString());
    }
}

void MyWidget::setTextColor(QColor color){
    ui->timeDisplay->setTextColor(color);
}

void MyWidget::setTextSize(int size){
    ui->timeDisplay->setFontPointSize(size);
    fontSize = size;
}

void MyWidget::setProgressBarVisibility(bool setting){
    ui->progressBar->setVisible(setting);
}

bool MyWidget::getProgressBarVisibility(){
    return (ui->progressBar->isVisible());
}

MyWidget::~MyWidget()
{
    delete ui;
}

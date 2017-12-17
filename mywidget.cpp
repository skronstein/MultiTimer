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

    //default values for when a new timer is created
    setWindowTitle("New Timer");
    windowTitleOnly = windowTitle();
    updateTimer.setInterval(1000);
    reminderBool = true;
    reminderBeforeDoneBool = true;
    reminderBeforeDoneShowedBool = false;
    reminderBeforeMins = 1;
    fontSize = 25;
    sDisplay = 0;
    ui->progressBar->setVisible(false);

    editTimerWindow *editTimer = new editTimerWindow(this);
    editTimerPtr = editTimer;
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    editTimer->show();
}


void MyWidget::on_EditButton_clicked()
{
    if(editTimerPtr->isHidden()){
        editTimerPtr->show();
    }
}

void MyWidget::setEndTime(QTime newEndTime){
    if(endTime != newEndTime || ui->progressBar->value()==100){
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
        QMessageBox::warning(this, "Invalid time error", "Invalid time error");
    }
}

void MyWidget::timeoutSlot(){
    if(updateTimerCounter < updateTimerInterval) updateTimerCounter ++;
    else{
        updateTimeDisplay();
        updateTimerCounter = 1;
    }
    checkIfTimeIsUp();
}

void MyWidget::checkIfTimeIsUp(){
    if(((float)(QTime::currentTime().secsTo(endTime) / 60 ) < (reminderBeforeMins)) && reminderBeforeDoneBool && !reminderBeforeDoneShowedBool){
        reminderBeforeDoneShowedBool = true;
        QMessageBox::information(this, QString::number(reminderBeforeMins) + " minutes until: " + windowTitle(),
                                       "Time is now " + QTime::currentTime().toString());
    }

    if(QTime::currentTime().secsTo(endTime) <= 0){
        updateTimeDisplay();//to set the timer to show 0 now that time is up
        updateTimer.stop();
        if(reminderBool) QMessageBox::information(this, "Time for: " + windowTitle(),
                                                        "Time is now " + QTime::currentTime().toString());
    }
}

void MyWidget::updateTimeDisplay(){

    int timeTo = QTime::currentTime().secsTo(endTime);
    int h, m;
    if(origTime > 0) ui->progressBar->setValue(100 - timeTo*100/origTime);
    if(timeTo < 0) timeTo = 0;

    h = timeTo / 3600;
    timeTo %= 3600;
    m = timeTo / 60;
    timeTo %= 60; //after this line, timeTo now represents the number of seconds to be displayed, not necessarily the number of seconds until the timer is up

    QString textToDisplay;

    //hours
    if(h != 0) textToDisplay.append(QString::number(h) + "h : ");

    //mins
    textToDisplay.append(QString::number(m) + "m");
    if(m < 10 && h != 0) textToDisplay.insert(textToDisplay.length()-2, "0"); //to display :01m instead of just :0s when the # if mins is a single digit #

    //seconds
    if(sDisplay > 0 || m == 0){ //   || m == 0   is to make the seconds display if less than 1 minutes is remaining
        textToDisplay.append(" : " + QString::number(timeTo)+ "s");
        if(timeTo < 10) textToDisplay.insert(textToDisplay.length()-2, "0"); //to display :01s instead of just :0s when the # if seconds is a single digit #
       }
    ui->timeDisplay->setText(textToDisplay);
}

void MyWidget::setTextColor(QColor color){
    ui->timeDisplay->setTextColor(color);
    ui->timeDisplay->setText(ui->timeDisplay->toPlainText());//to update the font color right when the user edits it
}

void MyWidget::setTextSize(int size){
    ui->timeDisplay->setFontPointSize(size);
    fontSize = size;
    ui->timeDisplay->setText(ui->timeDisplay->toPlainText());//to update the font size right when the user edits the spinbox value
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

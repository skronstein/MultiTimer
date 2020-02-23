#include <QTime>
#include "childwindow.h"
#include "mywidget.h"
#include "ui_mywidget.h"
#include "edittimerwindow.h"
#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include <QProgressBar>
#include "timeisupdialog.h"

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
    parentWidget()->resize(285, 150);

    editTimerPtr = new editTimerWindow(this);
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    editTimerPtr->show();
}


void MyWidget::on_EditButton_clicked()
{
    if(editTimerPtr->isHidden()){
        editTimerPtr->show();
    }
}

void MyWidget::setEndTime(QTime newEndTime){
    if(endDateTime.time() != newEndTime || ui->progressBar->value()==100){
        endDateTime.setTime(newEndTime);
        endDateTime.setDate(QDateTime::currentDateTime().date());
        if(endDateTime.time() < QTime::currentTime()) endDateTime = endDateTime.addDays(QDateTime::currentDateTime().daysTo(endDateTime)+1);
        origTime = QDateTime::currentDateTime().secsTo(endDateTime);
    }
}


void MyWidget::setDuration(int hours, int mins){
    QDateTime newDateTime = QDateTime::currentDateTime();

    newDateTime = newDateTime.addSecs(mins * 60);
    newDateTime = newDateTime.addSecs(hours * 3600);

    if(newDateTime.isValid()) {
         endDateTime.setTime(newDateTime.time());
         endDateTime.setDate(newDateTime.date());
         origTime = QDateTime::currentDateTime().secsTo(endDateTime);
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

    //reminder X number of minutes before time is up
    if(((float)(QDateTime::currentDateTime().secsTo(endDateTime) / 60 ) < (reminderBeforeMins)) && reminderBeforeDoneBool && !reminderBeforeDoneShowedBool){
        reminderBeforeDoneShowedBool = true;
        QMessageBox::information(this, QString::number(QDateTime().currentDateTime().secsTo(endDateTime) / 60 + 1) + " minutes until: " + windowTitle(),
                                       "Time is now " + QTime::currentTime().toString());
    }

    //reminder when time is up
    if(QDateTime::currentDateTime().secsTo(endDateTime) <= 0){
        updateTimeDisplay();//to set the timer to show 0 now that time is up
        updateTimer.stop();
        if(reminderBool /*&& origTime > 0*/) {
            TIUDialog = new TimeIsUpDialog(this);
            TIUDialog->show();
            TIUDialog->setAttribute(Qt::WA_DeleteOnClose);
            QApplication::beep();
        }
    }
}

void MyWidget::restartAfterFin(){
    setEndTime(endDateTime.addSecs(origTime).time());
    editTimerPtr->startMywidgetTimer();
    TIUDialog->close();
}

void MyWidget::restartAfterCurrentTime(){
    setEndTime(QTime::currentTime().addSecs(origTime));
    editTimerPtr->startMywidgetTimer();
    TIUDialog->close();
}

void MyWidget::closeTimer()
{
    if(TIUDialog != nullptr) TIUDialog->close();
    this->parentWidget()->close();
    TIUDialog = nullptr;
}

void MyWidget::minimizeTimer()
{
    if(TIUDialog != nullptr) TIUDialog->close();
    this->parentWidget()->setWindowState(Qt::WindowMinimized);
    TIUDialog = nullptr;
}

void MyWidget::updateTimeDisplay(){

    int timeTo = QDateTime::currentDateTime().secsTo(endDateTime);
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
    if(m < 10 && h != 0) textToDisplay.insert(textToDisplay.length()-2, "0"); //to display :01m instead of just :0m when the # if mins is a single digit #

    //seconds
    if(sDisplay > 0 || (m == 0 && h == 0)){ //   || m == 0   is to make the seconds display if less than 1 minutes is remaining
        textToDisplay.append(" : " + QString::number(timeTo)+ "s");
        if(timeTo < 10) textToDisplay.insert(textToDisplay.length()-2, "0"); //to display :01s instead of just :0s when the # if seconds is a single digit #
       }
    ui->timeDisplay->setText(textToDisplay);
    adjustTextSize();
}

void MyWidget::resizeEvent(QResizeEvent *event){
     QWidget::resizeEvent(event);
    adjustTextSize();
}

void MyWidget::adjustTextSize(){
    int size;
    size = (ui->timeDisplay->width() - 20) / ((ui->timeDisplay->toPlainText().length() / 1.8) + 1);
    if(ui->timeDisplay->height() * 0.5 < size) size = ui->timeDisplay->height() * 0.5;
    setTextSize(size);

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


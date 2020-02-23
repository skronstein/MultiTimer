#include "timeisupdialog.h"
#include "ui_timeisupdialog.h"

TimeIsUpDialog::TimeIsUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeIsUpDialog)
{
    ui->setupUi(this);
    widgetPtr = (MyWidget*)(this->parent());
    connect(ui->RestartAfterFinishedButton, SIGNAL(clicked(bool)), this->widgetPtr, SLOT(restartAfterFin()));
    connect(ui->RestartAfterCurrentTimeButton, SIGNAL(clicked(bool)), this->widgetPtr, SLOT(restartAfterCurrentTime()));
    connect(ui->CloseTimerButton, SIGNAL(clicked(bool)), this->widgetPtr, SLOT(closeTimer()));
    connect(ui->MinimizeTimerButton, SIGNAL(clicked(bool)), this->widgetPtr, SLOT(minimizeTimer()));
    setWindowTitle("Time for: " + widgetPtr->windowTitleOnly);

    timer.setInterval(1000);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(flashText()));
}

void TimeIsUpDialog::flashText(){
    if(QTime::currentTime().second() % 2)
        ui->label->setStyleSheet("QLabel { color : red }");
    else
        ui->label->setStyleSheet("QLabel { color : black }");
}

TimeIsUpDialog::~TimeIsUpDialog()
{
    delete ui;
}

void TimeIsUpDialog::on_RestartNextDayButton_clicked()
{
    widgetPtr->endDateTime.setDate(QDate::currentDate().addDays(1));
    widgetPtr->editTimerPtr->startMywidgetTimer();
    close();
}

void TimeIsUpDialog::on_EditTimerButton_clicked()
{
    widgetPtr->editTimerPtr->show();
    close();
}

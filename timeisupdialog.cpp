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
}

TimeIsUpDialog::~TimeIsUpDialog()
{
    delete ui;
}

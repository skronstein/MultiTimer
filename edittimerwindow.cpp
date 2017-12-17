#include "edittimerwindow.h"
#include "ui_edittimerwindow.h"
#include "mywidget.h"
#include <QTime>
#include <QDebug>
#include <QColorDialog>
#include <QColor>
#include <QString>

editTimerWindow::editTimerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editTimerWindow)
{
    ui->setupUi(this);


    widgetPtr = (MyWidget*)(this->parent());
    setWindowTitle("Edit: " + widgetPtr->windowTitle());

    connect(ui->showEndTimeCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWindowTitle()));

    //default values
    ui->lineEdit_windowTitle->setText(widgetPtr->windowTitleOnly);
    ui->updateIntervalSpinBox->setValue(widgetPtr->updateTimer.interval() / 1000);
    if(ui->updateIntervalSpinBox->value() == 0) ui->updateIntervalSpinBox->setValue(4);
    ui->endTimeRadioButton->setChecked(true);
    ui->fontSizeSpinBox->setValue(widgetPtr->fontSize);
    ui->reminderCheckBox->setChecked(widgetPtr->reminderBool);
    ui->reminderBeforeDoneCheckBox->setChecked(widgetPtr->reminderBeforeDoneBool);
    ui->reminderBeforeDoneSpinBox->setValue(widgetPtr->reminderBeforeMins);
    ui->timeEdit->setTime(widgetPtr->endTime);
    ui->showProgressBarCheckBox->setChecked(widgetPtr->getProgressBarVisibility());
    ui->showEndTimeCheckBox->setChecked(widgetPtr->displayTimeInTitle);

    QColorDialog *colorDialog = new QColorDialog(this);
    colorDialogPtr = colorDialog;
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), this,  SLOT(setFontColor()));
}


void editTimerWindow::on_createButton_clicked() //button text was renamed to "Start Timer"
{
    if(ui->endTimeRadioButton->isChecked())       widgetPtr->setEndTime(ui->timeEdit->time());
    else if(ui->durationRadioButton->isChecked()) widgetPtr->setDuration(ui->hoursSpinBox->value(), ui->minutesSpinBox->value());
    widgetPtr->updateTimer.start();
    widgetPtr->reminderBeforeDoneShowedBool = false;
    updateWindowTitle();
    widgetPtr->updateTimerCounter = 1;
    widgetPtr->updateTimeDisplay();
    widgetPtr->adjustTextSize();
    hide();
}


void editTimerWindow::updateWindowTitle()
{
    QString str;
    str = widgetPtr->windowTitleOnly = ui->lineEdit_windowTitle->text();
    if(ui->showEndTimeCheckBox->isChecked()) str.append(" at " + widgetPtr->endTime.toString());
    widgetPtr->setWindowTitle(str);
    widgetPtr->displayTimeInTitle = ui->showEndTimeCheckBox->isChecked();
    setWindowTitle("Edit: " + widgetPtr->windowTitle());
}


editTimerWindow::~editTimerWindow()
{
    delete ui;
}

void editTimerWindow::on_cancelButton_clicked() //button text was renamed to "Close"
{
    hide();
    colorDialogPtr->hide();
}

void editTimerWindow::on_fontColorButton_clicked()
{
    colorDialogPtr->show();
}

void editTimerWindow::redirectColorSlot(QColor color){
    widgetPtr->setTextColor(color);
}

void editTimerWindow::setFontColor(){
    widgetPtr->setTextColor(colorDialogPtr->currentColor());
}

void editTimerWindow::on_fontSizeSpinBox_valueChanged(int arg1)
{
    widgetPtr->setTextSize(arg1);
}

void editTimerWindow::on_displaySecondsCheckbox_toggled(bool checked)
{
    widgetPtr->sDisplay = checked;
    widgetPtr->updateTimeDisplay();
    widgetPtr->adjustTextSize();
}

void editTimerWindow::on_reminderCheckBox_toggled(bool checked)
{
    widgetPtr->reminderBool = checked;
    }

void editTimerWindow::on_reminderBeforeDoneCheckBox_toggled(bool checked)
{
    widgetPtr->reminderBeforeDoneBool = checked;
    widgetPtr->reminderBeforeMins = ui->reminderBeforeDoneSpinBox->value();
}

void editTimerWindow::on_showProgressBarCheckBox_toggled(bool checked)
{
    widgetPtr->setProgressBarVisibility(checked);
}

void editTimerWindow::on_updateIntervalSpinBox_valueChanged(int arg1)
{
    widgetPtr->updateTimerInterval = abs((ui->updateIntervalSpinBox->value()));
}

void editTimerWindow::on_lineEdit_windowTitle_textEdited(const QString &arg1)
{
    widgetPtr->windowTitleOnly = ui->lineEdit_windowTitle->text();
    updateWindowTitle();
}



void editTimerWindow::changeToEndTime(){
    ui->endTimeRadioButton->setChecked(true);
}

void editTimerWindow::changeToDuration(){
    ui->durationRadioButton->setChecked(true);
}



void editTimerWindow::on_timeEdit_timeChanged(const QTime &time)
{
    changeToEndTime();
}

void editTimerWindow::on_hoursSpinBox_valueChanged(int arg1)
{
    changeToDuration();
}

void editTimerWindow::on_minutesSpinBox_valueChanged(int arg1)
{
    changeToDuration();
}

void editTimerWindow::on_reminderBeforeDoneSpinBox_valueChanged(int arg1)
{
    widgetPtr->reminderBeforeMins = ui->reminderBeforeDoneSpinBox->value();
}

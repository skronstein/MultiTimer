#ifndef EDITTIMERWINDOW_H
#define EDITTIMERWINDOW_H

#include <QDialog>
#include <QColorDialog>
#include <QColor>
#include "mywidget.h"

class MyWidget;

namespace Ui {
class editTimerWindow;
}

class editTimerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editTimerWindow(QWidget *parent = 0);
    ~editTimerWindow();
    void changeToEndTime();
    void changeToDuration();

signals:
    void redirectTime();

public slots:
    void setFontColor();
    void redirectColorSlot(QColor color);
    void on_createButton_clicked();
    void startMywidgetTimer();

private slots:
    void updateWindowTitle();

    void on_cancelButton_clicked();


    void on_fontColorButton_clicked();

    void on_fontSizeSpinBox_valueChanged(int arg1);

    void on_reminderCheckBox_toggled(bool checked);

    void on_reminderBeforeDoneCheckBox_toggled(bool checked);

    void on_showProgressBarCheckBox_toggled(bool checked);

    void on_updateIntervalSpinBox_valueChanged(int arg1);

    void on_lineEdit_windowTitle_textEdited(const QString &arg1);

    void on_timeEdit_timeChanged(const QTime &time);

    void on_hoursSpinBox_valueChanged(int arg1);

    void on_minutesSpinBox_valueChanged(int arg1);

    void on_reminderBeforeDoneSpinBox_valueChanged(int arg1);

    void on_displaySecondsCheckbox_toggled(bool checked);


private:
    Ui::editTimerWindow *ui;
    QColorDialog *colorDialogPtr;
    MyWidget *widgetPtr;
};

#endif // EDITTIMERWINDOW_H

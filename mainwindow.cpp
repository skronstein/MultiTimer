#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include "childwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MultiTimer");
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    timeFormatString.fromStdString("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayAbout(){
    QMessageBox::information(this, "About Timer","Version 1.02");
}

void MainWindow::createChild(){
    ChildWindow *childwindow = new ChildWindow(ui->mdiArea);
    childwindow->setAttribute(Qt::WA_DeleteOnClose);
    childwindow->show();
    connect(ui->actionUse_24_hour_Time, SIGNAL(toggled(bool)), childwindow->mywidget->editTimerPtr, SLOT(updateWindowTitle()));
}


void MainWindow::on_actionUse_24_hour_Time_triggered()
{
    if(ui->actionUse_24_hour_Time->isChecked()) timeFormatString.fromStdString("");
    else timeFormatString.fromStdString("h:mm:ss ap");
}

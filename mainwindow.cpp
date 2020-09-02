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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayAbout(){
    QMessageBox::information(this, "About Timer","Version 1.03");
}

void MainWindow::createChild(){
    ChildWindow *childwindow = new ChildWindow(ui->mdiArea);
    childwindow->setAttribute(Qt::WA_DeleteOnClose);
    childwindow->show();
}


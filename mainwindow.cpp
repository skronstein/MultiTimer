#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayAbout()
{
  QMessageBox::about(this, tr("About this demo"),
    tr("<p>This is a nice demo with <i>some</i> "
       "<u>crazy</u> HTML content.</p>"));
}

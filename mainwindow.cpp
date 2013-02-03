#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "childwindow.h"

#include <QtGui>
#include <QMdiArea>
#include <QMdiSubWindow>

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

void MainWindow::createChild()
{
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea);
    childWindow->setAttribute(Qt::WA_DeleteOnClose);
    childWindow->show();
}

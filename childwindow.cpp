#include "childwindow.h"
#include <QMdiSubWindow>
#include "mywidget.h"

ChildWindow::ChildWindow(QWidget *parent) :
QMdiSubWindow(parent)
{
    mywidget = new MyWidget(this);
    this->setWidget(mywidget);
    }

ChildWindow::~ChildWindow(){
    mywidget->~MyWidget();
}

#include "childwindow.h"
#include <QMdiSubWindow>
#include "mywidget.h"

ChildWindow::ChildWindow(QWidget *parent) :
QMdiSubWindow(parent)
{
    mywidget = new MyWidget(this);
    this->setWidget(mywidget);
    setGeometry(0,0,363,height());
}

ChildWindow::~ChildWindow(){
    mywidget->~MyWidget();
}

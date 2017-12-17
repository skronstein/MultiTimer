#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QtGui>
#include <QWidget>
#include <QMdiSubWindow>

#include "mywidget.h"

namespace Ui{    class ChildWindow; }


class ChildWindow : public QMdiSubWindow
{
        Q_OBJECT

public:
    explicit ChildWindow(QWidget *parent = 0);
    ~ChildWindow();

private:
    MyWidget *mywidget;
    //virtual void resizeEvent(QResizeEvent *resizeEvent);
};

#endif // CHILDWINDOW_H

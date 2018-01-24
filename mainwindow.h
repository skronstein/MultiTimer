#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString timeFormatString;
    ~MainWindow();

public slots:
    void displayAbout();
    void createChild();

private slots:
    void on_actionUse_24_hour_Time_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

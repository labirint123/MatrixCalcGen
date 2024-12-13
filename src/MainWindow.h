#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMainWindow window;
public:
    Controller *cont;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
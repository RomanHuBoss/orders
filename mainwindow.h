#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "db.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Db * db;
public:
    MainWindow(Db * db, QWidget * parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

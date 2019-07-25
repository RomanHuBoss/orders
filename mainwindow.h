#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QTreeWidget>
#include "db.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Db * db;

    QTableWidget * projectsTbl;
    QTreeWidget * tasksTree;
    QTreeWidget * commentsTree;

public:
    MainWindow(Db * db, QWidget * parent = 0);
    void setupGui();
    ~MainWindow();
};

#endif // MAINWINDOW_H

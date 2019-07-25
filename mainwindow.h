#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QTreeWidget>
#include "db.h"
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Db * db;

    QTableWidget * projectsTbl;
    QTreeWidget * tasksTree;
    QTreeWidget * commentsTree;

    QPushButton * addProjectBtn;
    QPushButton * removeProjectBtn;

    QPushButton * editTaskBtn;
    QPushButton * addTaskBtn;
    QPushButton * addSubtaskBtn;
    QPushButton * removeTaskBtn;

    QPushButton * editCommentBtn;
    QPushButton * addCommentBtn;
    QPushButton * addSubcommentBtn;
    QPushButton * removeCommentBtn;

public:
    MainWindow(Db * db, QWidget * parent = 0);
    void setupGui();
    ~MainWindow();
};

#endif // MAINWINDOW_H

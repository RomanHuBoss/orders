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

    QPushButton * detailsProjectBtn;
    QPushButton * addProjectBtn;
    QPushButton * editProjectBtn;
    QPushButton * removeProjectBtn;

    QPushButton * detailsTaskBtn;
    QPushButton * editTaskBtn;
    QPushButton * addTaskBtn;
    QPushButton * addSubtaskBtn;
    QPushButton * removeTaskBtn;

    QPushButton * detailsCommentBtn;
    QPushButton * editCommentBtn;
    QPushButton * addCommentBtn;
    QPushButton * addSubcommentBtn;
    QPushButton * removeCommentBtn;

public:
    MainWindow(Db * db, QWidget * parent = nullptr);
    void setupGUI();
    ~MainWindow();
};

#endif // MAINWINDOW_H

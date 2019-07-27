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
private slots:
    void onSelectProject();
    void onShowProjectDetailsDialog();
    void onShowProjectAddDialog();
    void onShowProjectEditDialog();
    void onRemoveProject();

    void onSelectTask();
    void onRefreshProjectsTbl();

protected:
    void fillProjectsTable();
    void fillTasksTree(const Rows& tasksData);
    void fillCommentsTree(const Rows &commentsData);
    void setupProjectsButtons();
};

#endif // MAINWINDOW_H

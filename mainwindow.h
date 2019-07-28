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
    void onRefreshProjectsTbl();
    void onShowProjectDetailsDialog();
    void onShowProjectAddDialog();
    void onShowProjectEditDialog();
    void onRemoveProject();


    void onSelectTask();
    void onRefreshTasksTree();
    void onShowTaskDetailsDialog();
    void onShowTaskAddDialog();
    void onShowSubtaskAddDialog();
    void onShowTaskEditDialog();
    void onRemoveTask();

    void onSelectComment();
    void onRefreshCommentsTree();
    void onShowCommentDetailsDialog();
    void onShowCommentAddDialog();
    void onShowSubcommentAddDialog();
    void onShowCommentEditDialog();
    void onRemoveComment();

protected:
    void fillProjectsTable();
    void fillTasksTree();
    void fillCommentsTree();
    void setupProjectsButtons();
    void setupTasksButtons();
    void setupCommentsButtons();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QToolBar>
#include <QGroupBox>
#include <QHeaderView>
#include <QButtonGroup>
#include "projectdialog.h"
#include <algorithm>

MainWindow::MainWindow(Db *db, QWidget * parent) :
    QMainWindow(parent), db(db)
{
    QString title = "Программа \"Распоряжения\" | " + db->getCurrentUser().getFio() + " (" + db->getCurrentUser().getPosition().getTitle() + ")";
    setWindowTitle(tr(title.toStdString().c_str()));
    setMinimumWidth(800);
    setupGUI();

    showMaximized();

    //заполнить список проектов
    fillProjectsTable();
}

void MainWindow::fillProjectsTable() {
    projectsTbl->blockSignals(true);
    while (projectsTbl->rowCount() > 0) {
        projectsTbl->removeRow(projectsTbl->rowCount() - 1);
    }

    Rows projectsData = db->getProjectsData();

    for (auto row : projectsData) {
        projectsTbl->insertRow(projectsTbl->rowCount());
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 0, new QTableWidgetItem(row["id"].toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 1, new QTableWidgetItem(row["title"].toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 2, new QTableWidgetItem(row["start_date"].toDate().toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 3, new QTableWidgetItem(row["end_date"].toDate().toString()));
        projectsTbl->item(projectsTbl->rowCount() - 1, 0)->setData(Qt::UserRole, row);
    }

    projectsTbl->blockSignals(false);

    if (projectsTbl->rowCount() > 0) {
        projectsTbl->selectRow(0);
    }

    setupProjectsButtons();
}

void MainWindow::fillTasksTree()
{
    tasksTree->blockSignals(true);
    tasksTree->clear();

    RowData row = qvariant_cast<RowData>(projectsTbl->item(projectsTbl->currentRow(), 0)->data(Qt::UserRole));
    int id_project = row["id"].toInt();

    Rows tasksData = db->getTasksData(id_project);
    while (tasksData.size()) {
        auto new_end = std::remove_if(tasksData.begin(), tasksData.end(), [&](const RowData& task) {
            QTreeWidgetItem * parent = nullptr;

            if (!task["pid"].isNull()) {
                QList<QTreeWidgetItem*> items = tasksTree->findItems(task["pid"].toString(), Qt::MatchFixedString | Qt::MatchContains | Qt::MatchRecursive, 0);

                if (items.size() == 0) {
                    return false;
                }

                parent = items[0];
            }

            QTreeWidgetItem * row = new QTreeWidgetItem;
            row->setData(0, Qt::UserRole, task);
            row->setText(0, task["id"].toString());
            row->setText(1, task["title"].toString());
            row->setText(2, task["fio"].toString());
            row->setText(3, task["status_title"].toString());
            row->setText(4, task["published_dt"].toDate().toString());
            row->setText(5, task["deadline_dt"].toDate().toString());

            if (parent == nullptr) {
                tasksTree->addTopLevelItem(row);
            }
            else {
                parent->addChild(row);
            }

            return true;
        });

        tasksData.erase(new_end, tasksData.end());
    }


    tasksTree->blockSignals(false);

    if (tasksTree->topLevelItemCount() > 0) {
        tasksTree->setCurrentItem(tasksTree->topLevelItem(0));
    }

    setupTasksButtons();

}

void MainWindow::fillCommentsTree()
{

}

void MainWindow::setupGUI()
{
    QToolBar* tb = new QToolBar(tr("Панель инструментов окна"));
    tb->addAction(QPixmap(":/Resources/report_icon.png"), tr("Отчет"), this, SLOT(slotNoImpl()));
    tb->addAction(QPixmap(":/Resources/users_icon.png"), tr("Пользователи"), this, SLOT(slotNoImpl()));
    tb->addAction(QPixmap(":/Resources/status_sequence_icon.png"), tr("Бизнес-процесс"), this, SLOT(slotNoImpl()));
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tb->addWidget(spacer);
    tb->addAction(QPixmap(":/Resources/about_icon.png"), tr("О программе"), this, SLOT(slotNoImpl()));

    addToolBar(Qt::TopToolBarArea, tb);


    QWidget * wgt = new QWidget(this);
    setCentralWidget(wgt);

    QHBoxLayout * mainLayout = new QHBoxLayout;
    wgt->setLayout(mainLayout);

    projectsTbl = new QTableWidget;
    projectsTbl->setColumnCount(3);
    projectsTbl->setHorizontalHeaderLabels(QStringList{tr("id"), tr("Название"), tr("Дата начала"), tr("Дата окончания")});
    projectsTbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    projectsTbl->horizontalHeader()->setStretchLastSection(true);
    projectsTbl->setSelectionBehavior(QAbstractItemView::SelectRows);
    projectsTbl->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    projectsTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(projectsTbl, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectProject()));

    detailsProjectBtn = new QPushButton;
    detailsProjectBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsProjectBtn->setText(tr("Подробности"));
    detailsProjectBtn->setFlat(true);
    detailsProjectBtn->setIconSize(QSize{24, 24});
    detailsProjectBtn->setDisabled(true);

    connect(detailsProjectBtn, SIGNAL(clicked()), this, SLOT(onShowProjectDetailsDialog()));

    addProjectBtn = new QPushButton;
    addProjectBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addProjectBtn->setText(tr("Создать проект"));
    addProjectBtn->setFlat(true);
    addProjectBtn->setIconSize(QSize{24, 24});
    addProjectBtn->setDisabled(true);

    connect(addProjectBtn, SIGNAL(clicked()), this, SLOT(onShowProjectAddDialog()));
    if (db->getCurrentUser().isHead()) {
        addProjectBtn->setDisabled(false);        
    }

    editProjectBtn = new QPushButton;
    editProjectBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editProjectBtn->setText(tr("Редактировать"));
    editProjectBtn->setFlat(true);
    editProjectBtn->setIconSize(QSize{24, 24});
    editProjectBtn->setDisabled(true);

    connect(editProjectBtn, SIGNAL(clicked()), this, SLOT(onShowProjectEditDialog()));

    removeProjectBtn = new QPushButton;
    removeProjectBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeProjectBtn->setText(tr("Удалить"));
    removeProjectBtn->setFlat(true);
    removeProjectBtn->setIconSize(QSize{24, 24});
    removeProjectBtn->setDisabled(true);

    connect(removeProjectBtn, SIGNAL(clicked()), this, SLOT(onRemoveProject()));

    QHBoxLayout * projectsBtns = new QHBoxLayout;
    projectsBtns->addStretch(1);
    projectsBtns->addWidget(detailsProjectBtn);
    projectsBtns->addWidget(addProjectBtn);
    projectsBtns->addWidget(editProjectBtn);
    projectsBtns->addWidget(removeProjectBtn);

    QGroupBox * projectsGroup  = new QGroupBox(tr("Проекты"));
    QVBoxLayout * projectsLayout = new QVBoxLayout;
    projectsGroup->setLayout(projectsLayout);
    projectsLayout->addWidget(projectsTbl);
    projectsLayout->addLayout(projectsBtns);

    projectsGroup->setMinimumWidth(500);

    mainLayout->addWidget(projectsGroup);

    QVBoxLayout * rightLayout = new QVBoxLayout;
    mainLayout->addLayout(rightLayout, 1);

    tasksTree = new QTreeWidget;
    tasksTree->setColumnCount(5);
    tasksTree->setHeaderLabels(QStringList{tr("id"), tr("Название"), tr("Ответственный"), tr("Статус"), tr("Дата создания"), tr("Плановое завершение")});
    tasksTree->header()->setSectionResizeMode(QHeaderView::Stretch);
    tasksTree->header()->setStretchLastSection(true);
    tasksTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tasksTree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    tasksTree->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(tasksTree, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectTask()));

    detailsTaskBtn = new QPushButton;
    detailsTaskBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsTaskBtn->setText(tr("Подробности"));
    detailsTaskBtn->setFlat(true);
    detailsTaskBtn->setIconSize(QSize{24, 24});
    detailsTaskBtn->setDisabled(true);

    connect(detailsTaskBtn, SIGNAL(clicked()), this, SLOT(onShowTaskDetailsDialog()));

    addTaskBtn = new QPushButton;
    addTaskBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addTaskBtn->setText(tr("Создать задачу"));
    addTaskBtn->setFlat(true);
    addTaskBtn->setIconSize(QSize{24, 24});
    addTaskBtn->setDisabled(true);

    connect(addTaskBtn, SIGNAL(clicked()), this, SLOT(onShowTaskAddDialog()));

    addSubtaskBtn = new QPushButton;
    addSubtaskBtn->setIcon(QPixmap(":/Resources/add_subobject.png"));
    addSubtaskBtn->setText(tr("Создать подзадачу"));
    addSubtaskBtn->setFlat(true);
    addSubtaskBtn->setIconSize(QSize{24, 24});
    addSubtaskBtn->setDisabled(true);

    connect(addSubtaskBtn, SIGNAL(clicked()), this, SLOT(onShowSubtaskAddDialog()));

    editTaskBtn = new QPushButton;
    editTaskBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editTaskBtn->setText(tr("Редактировать"));
    editTaskBtn->setFlat(true);
    editTaskBtn->setIconSize(QSize{24, 24});
    editTaskBtn->setDisabled(true);

    connect(editTaskBtn, SIGNAL(clicked()), this, SLOT(onShowTaskEditDialog()));

    removeTaskBtn = new QPushButton;
    removeTaskBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeTaskBtn->setText(tr("Удалить"));
    removeTaskBtn->setFlat(true);
    removeTaskBtn->setIconSize(QSize{24, 24});
    removeTaskBtn->setDisabled(true);

    connect(removeTaskBtn, SIGNAL(clicked()), this, SLOT(onRemoveTask()));

    QHBoxLayout * tasksTreeBtns = new QHBoxLayout;
    tasksTreeBtns->addStretch(1);
    tasksTreeBtns->addWidget(detailsTaskBtn);
    tasksTreeBtns->addWidget(addTaskBtn);
    tasksTreeBtns->addWidget(addSubtaskBtn);
    tasksTreeBtns->addWidget(editTaskBtn);
    tasksTreeBtns->addWidget(removeTaskBtn);

    QGroupBox * tasksGroup = new QGroupBox;
    tasksGroup->setTitle(tr("Задачи проекта"));
    QVBoxLayout * tasksLayout = new QVBoxLayout;
    tasksGroup->setLayout(tasksLayout);
    tasksLayout->addWidget(tasksTree);
    tasksLayout->addLayout(tasksTreeBtns);

    rightLayout->addWidget(tasksGroup, 1);

    commentsTree = new QTreeWidget;
    commentsTree->setColumnCount(3);
    commentsTree->setHeaderLabels(QStringList{tr("id"), tr("Тема комментария"), tr("Автор"), tr("Дата создания")});
    commentsTree->header()->setSectionResizeMode(QHeaderView::Stretch);
    commentsTree->header()->setStretchLastSection(true);
    commentsTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    commentsTree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    commentsTree->setEditTriggers(QAbstractItemView::NoEditTriggers);

    detailsCommentBtn = new QPushButton;
    detailsCommentBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsCommentBtn->setText(tr("Подробности"));
    detailsCommentBtn->setFlat(true);
    detailsCommentBtn->setIconSize(QSize{24, 24});
    detailsCommentBtn->setDisabled(true);

    connect(detailsCommentBtn, SIGNAL(clicked()), this, SLOT(onShowCommentDetailsDialog()));

    addCommentBtn = new QPushButton;
    addCommentBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addCommentBtn->setText(tr("Добавить комментарий"));
    addCommentBtn->setFlat(true);
    addCommentBtn->setIconSize(QSize{24, 24});
    addCommentBtn->setDisabled(true);

    connect(addCommentBtn, SIGNAL(clicked()), this, SLOT(onShowCommentAddDialog()));

    addSubcommentBtn = new QPushButton;
    addSubcommentBtn->setIcon(QPixmap(":/Resources/add_subobject.png"));
    addSubcommentBtn->setText(tr("Ответить"));
    addSubcommentBtn->setFlat(true);
    addSubcommentBtn->setIconSize(QSize{24, 24});
    addSubcommentBtn->setDisabled(true);

    connect(addSubcommentBtn, SIGNAL(clicked()), this, SLOT(onShowSubcommentAddDialog()));

    editCommentBtn = new QPushButton;
    editCommentBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editCommentBtn->setText(tr("Редактировать"));
    editCommentBtn->setFlat(true);
    editCommentBtn->setIconSize(QSize{24, 24});
    editCommentBtn->setDisabled(true);

    connect(editCommentBtn, SIGNAL(clicked()), this, SLOT(onShowCommentEditDialog()));

    removeCommentBtn = new QPushButton;
    removeCommentBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeCommentBtn->setText(tr("Удалить"));
    removeCommentBtn->setFlat(true);
    removeCommentBtn->setIconSize(QSize{24, 24});
    removeCommentBtn->setDisabled(true);

    connect(removeCommentBtn, SIGNAL(clicked()), this, SLOT(onRemoveComment()));

    QHBoxLayout * commentsTreeBtns = new QHBoxLayout;
    commentsTreeBtns->addStretch(1);
    commentsTreeBtns->addWidget(detailsCommentBtn);
    commentsTreeBtns->addWidget(addCommentBtn);
    commentsTreeBtns->addWidget(addSubcommentBtn);
    commentsTreeBtns->addWidget(editCommentBtn);
    commentsTreeBtns->addWidget(removeCommentBtn);

    QGroupBox * commentsGroup = new QGroupBox;
    commentsGroup->setTitle(tr("Комментарии к задаче"));
    QVBoxLayout * commentsLayout = new QVBoxLayout;
    commentsGroup->setLayout(commentsLayout);
    commentsLayout->addWidget(commentsTree);
    commentsLayout->addLayout(commentsTreeBtns);

    rightLayout->addWidget(commentsGroup, 1);
}



MainWindow::~MainWindow()
{
    delete db;
}

void MainWindow::setupTasksButtons() {
    if (tasksTree->selectedItems().size() > 0) {
        RowData row = qvariant_cast<RowData>(tasksTree->selectedItems()[0]->data(0, Qt::UserRole));
        detailsTaskBtn->setDisabled(false);
        addTaskBtn->setDisabled(!db->getCurrentUser().isHead());
        addSubtaskBtn->setDisabled(!db->getCurrentUser().isHead());
        editTaskBtn->setDisabled(db->getCurrentUser().getId() != row["id_worker"].toInt() && !db->getCurrentUser().isHead());
        removeTaskBtn->setDisabled(!db->getCurrentUser().isHead());
    }
    else {
        detailsTaskBtn->setDisabled(true);
        addTaskBtn->setDisabled(!projectsTbl->selectedItems().size() || !db->getCurrentUser().isHead());
        addSubtaskBtn->setDisabled(true);
        editTaskBtn->setDisabled(true);
        removeTaskBtn->setDisabled(true);
    }
}

void MainWindow::setupCommentsButtons()
{

}

void MainWindow::setupProjectsButtons()
{
    addProjectBtn->setDisabled(!db->getCurrentUser().isHead());

    if (projectsTbl->currentRow() >= 0) {
        detailsProjectBtn->setDisabled(false);
        editProjectBtn->setDisabled(!db->getCurrentUser().isHead());
        removeProjectBtn->setDisabled(!db->getCurrentUser().isHead());
    }
    else {
        detailsProjectBtn->setDisabled(true);
        editProjectBtn->setDisabled(true);
        removeProjectBtn->setDisabled(true);
    }
}

void MainWindow::onSelectProject()
{
    setupProjectsButtons();
    fillTasksTree();
}

void MainWindow::onShowProjectDetailsDialog()
{
    RowData row = qvariant_cast<RowData>(projectsTbl->item(projectsTbl->currentRow(), 0)->data(Qt::UserRole));

    ProjectDialog pd(row, SHOW, db);
    pd.exec();

}

void MainWindow::onShowProjectAddDialog()
{
    ProjectDialog pd(RowData(), ADD, db);
    connect(&pd, SIGNAL(raiseDataChanged()), this, SLOT(onRefreshProjectsTbl()));
    pd.exec();

}

void MainWindow::onShowProjectEditDialog()
{
    RowData row = qvariant_cast<RowData>(projectsTbl->item(projectsTbl->currentRow(), 0)->data(Qt::UserRole));
    ProjectDialog pd(row, EDIT, db);
    connect(&pd, SIGNAL(raiseDataChanged()), this, SLOT(onRefreshProjectsTbl()));
    pd.exec();

}

void MainWindow::onRemoveProject()
{
    RowData row = qvariant_cast<RowData>(projectsTbl->item(projectsTbl->currentRow(), 0)->data(Qt::UserRole));
    if (db->removeProject(row)) {
        fillProjectsTable();
    }
}

void MainWindow::onSelectTask()
{
    setupTasksButtons();
    fillCommentsTree();
}

void MainWindow::onSelectComment()
{
    setupCommentsButtons();
}


void MainWindow::onRefreshProjectsTbl()
{
    fillProjectsTable();
}


void MainWindow::onRemoveTask()
{
    RowData row = qvariant_cast<RowData>(tasksTree->selectedItems()[0]->data(0, Qt::UserRole));
    if (db->removeTask(row)) {
        fillTasksTree();
    }
}

void MainWindow::onRefreshTasksTree()
{
    fillTasksTree();
}

void MainWindow::onShowTaskDetailsDialog()
{

}

void MainWindow::onShowTaskAddDialog()
{

}

void MainWindow::onShowSubtaskAddDialog()
{

}

void MainWindow::onShowTaskEditDialog()
{

}

void MainWindow::onRefreshCommentsTree()
{
    fillCommentsTree();
}

void MainWindow::onShowCommentDetailsDialog()
{

}

void MainWindow::onShowCommentAddDialog()
{

}

void MainWindow::onShowSubcommentAddDialog()
{

}

void MainWindow::onShowCommentEditDialog()
{

}

void MainWindow::onRemoveComment()
{

}

#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QToolBar>
#include <QGroupBox>
#include <QHeaderView>
#include <QButtonGroup>
#include "projectdetailsdialog.h"

MainWindow::MainWindow(Db *db, QWidget * parent) :
    QMainWindow(parent), db(db)
{
    QString title = "Программа \"Распоряжения\" | " + db->getCurrentUser().getFio() + " (" + db->getCurrentUser().getPosition().getTitle() + ")";
    setWindowTitle(tr(title.toStdString().c_str()));
    setWindowIcon(QPixmap(":/Resources/window_title_icon.png"));
    setMinimumWidth(800);
    setupGUI();

    showMaximized();

    //заполнить список проектов
    fillProjectsTable();
}

void MainWindow::fillProjectsTable() {
    projectsTbl->clear();

    Rows projectsData = db->getProjectsData();

    for (auto row : projectsData) {
        projectsTbl->insertRow(projectsTbl->rowCount());
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 0, new QTableWidgetItem(row["title"].toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 1, new QTableWidgetItem(row["start_date"].toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 2, new QTableWidgetItem(row["end_date"].toString()));
        projectsTbl->item(projectsTbl->rowCount() - 1, 0)->setData(Qt::UserRole, row);
    }
}

void MainWindow::fillTasksTree(const Rows &tasksData)
{
    tasksTree->clear();

    for (auto row : tasksData) {
    }

}

void MainWindow::fillCommentsTree(const Rows &commentsData)
{
    commentsTree->clear();

    for (auto row : commentsData) {
    }

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
    projectsTbl->setHorizontalHeaderLabels(QStringList{tr("Название"), tr("Дата начала"), tr("Дата окончания")});
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

    if (db->getCurrentUser().isHead()) {
        addProjectBtn->setDisabled(false);
    }

    editProjectBtn = new QPushButton;
    editProjectBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editProjectBtn->setText(tr("Редактировать"));
    editProjectBtn->setFlat(true);
    editProjectBtn->setIconSize(QSize{24, 24});
    editProjectBtn->setDisabled(true);

    removeProjectBtn = new QPushButton;
    removeProjectBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeProjectBtn->setText(tr("Удалить"));
    removeProjectBtn->setFlat(true);
    removeProjectBtn->setIconSize(QSize{24, 24});
    removeProjectBtn->setDisabled(true);

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
    tasksTree->setHeaderLabels(QStringList{tr("Название"), tr("Ответственный"), tr("Статус"), tr("Дата создания"), tr("Плановое завершение")});
    tasksTree->header()->setSectionResizeMode(QHeaderView::Stretch);
    tasksTree->header()->setStretchLastSection(true);
    tasksTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tasksTree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    tasksTree->setEditTriggers(QAbstractItemView::NoEditTriggers);

    detailsTaskBtn = new QPushButton;
    detailsTaskBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsTaskBtn->setText(tr("Подробности"));
    detailsTaskBtn->setFlat(true);
    detailsTaskBtn->setIconSize(QSize{24, 24});
    detailsTaskBtn->setDisabled(true);

    addTaskBtn = new QPushButton;
    addTaskBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addTaskBtn->setText(tr("Создать задачу"));
    addTaskBtn->setFlat(true);
    addTaskBtn->setIconSize(QSize{24, 24});
    addTaskBtn->setDisabled(true);



    addSubtaskBtn = new QPushButton;
    addSubtaskBtn->setIcon(QPixmap(":/Resources/add_subobject.png"));
    addSubtaskBtn->setText(tr("Создать подзадачу"));
    addSubtaskBtn->setFlat(true);
    addSubtaskBtn->setIconSize(QSize{24, 24});
    addSubtaskBtn->setDisabled(true);

    editTaskBtn = new QPushButton;
    editTaskBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editTaskBtn->setText(tr("Редактировать"));
    editTaskBtn->setFlat(true);
    editTaskBtn->setIconSize(QSize{24, 24});
    editTaskBtn->setDisabled(true);

    removeTaskBtn = new QPushButton;
    removeTaskBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeTaskBtn->setText(tr("Удалить"));
    removeTaskBtn->setFlat(true);
    removeTaskBtn->setIconSize(QSize{24, 24});
    removeTaskBtn->setDisabled(true);

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
    commentsTree->setHeaderLabels(QStringList{tr("Тема комментария"), tr("Автор"), tr("Дата создания")});
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

    addCommentBtn = new QPushButton;
    addCommentBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addCommentBtn->setText(tr("Добавить комментарий"));
    addCommentBtn->setFlat(true);
    addCommentBtn->setIconSize(QSize{24, 24});
    addCommentBtn->setDisabled(true);

    addSubcommentBtn = new QPushButton;
    addSubcommentBtn->setIcon(QPixmap(":/Resources/add_subobject.png"));
    addSubcommentBtn->setText(tr("Ответить"));
    addSubcommentBtn->setFlat(true);
    addSubcommentBtn->setIconSize(QSize{24, 24});
    addSubcommentBtn->setDisabled(true);

    editCommentBtn = new QPushButton;
    editCommentBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editCommentBtn->setText(tr("Редактировать"));
    editCommentBtn->setFlat(true);
    editCommentBtn->setIconSize(QSize{24, 24});
    editCommentBtn->setDisabled(true);

    removeCommentBtn = new QPushButton;
    removeCommentBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeCommentBtn->setText(tr("Удалить"));
    removeCommentBtn->setFlat(true);
    removeCommentBtn->setIconSize(QSize{24, 24});
    removeCommentBtn->setDisabled(true);

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

void MainWindow::onSelectProject()
{
    detailsProjectBtn->setDisabled(false);
    addProjectBtn->setDisabled(!db->getCurrentUser().isHead());
    editProjectBtn->setDisabled(!db->getCurrentUser().isHead());
    removeProjectBtn->setDisabled(!db->getCurrentUser().isHead());

    RowData row = qvariant_cast<RowData>(projectsTbl->item(projectsTbl->currentRow(), 0)->data(Qt::UserRole));

    int id_project = row["id"].toInt();

    Rows tasksData = db->getTasksData(id_project);

    if (tasksData.size() > 0) {
        fillTasksTree(tasksData);
    }
}

void MainWindow::onShowProjectDetailsDialog()
{
    RowData row = qvariant_cast<RowData>(projectsTbl->item(projectsTbl->currentRow(), 0)->data(Qt::UserRole));

    ProjectDetailsDialog(row).exec();
}

void MainWindow::onSelectTask()
{

    commentsTree->clear();

    QList<QTreeWidgetItem *> items = tasksTree->selectedItems();
    RowData row = qvariant_cast<RowData>(items.at(0)->data(0, Qt::UserRole));

    int id_task = row["id"].toInt();

    Rows commentsData = db->getCommentsData(id_task);
}

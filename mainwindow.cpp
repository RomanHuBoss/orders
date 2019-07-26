#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QToolBar>
#include <QGroupBox>
#include <QHeaderView>
#include <QButtonGroup>

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
    QVector<QMap<QString, QVariant>> projectsData = db->getProjectsData();

    for (auto row : projectsData) {
        projectsTbl->insertRow(projectsTbl->rowCount());
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 0, new QTableWidgetItem(row["title"].toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 1, new QTableWidgetItem(row["title"].toString()));
        projectsTbl->setItem( projectsTbl->rowCount() - 1, 2, new QTableWidgetItem(row["title"].toString()));
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

    detailsProjectBtn = new QPushButton;
    detailsProjectBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsProjectBtn->setText(tr("Подробности"));
    detailsProjectBtn->setFlat(true);
    detailsProjectBtn->setIconSize(QSize{24, 24});

    addProjectBtn = new QPushButton;
    addProjectBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addProjectBtn->setText(tr("Создать проект"));
    addProjectBtn->setFlat(true);
    addProjectBtn->setIconSize(QSize{24, 24});

    editProjectBtn = new QPushButton;
    editProjectBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editProjectBtn->setText(tr("Редактировать"));
    editProjectBtn->setFlat(true);
    editProjectBtn->setIconSize(QSize{24, 24});

    removeProjectBtn = new QPushButton;
    removeProjectBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeProjectBtn->setText(tr("Удалить"));
    removeProjectBtn->setFlat(true);
    removeProjectBtn->setIconSize(QSize{24, 24});

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

    detailsTaskBtn = new QPushButton;
    detailsTaskBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsTaskBtn->setText(tr("Подробности"));
    detailsTaskBtn->setFlat(true);
    detailsTaskBtn->setIconSize(QSize{24, 24});

    addTaskBtn = new QPushButton;
    addTaskBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addTaskBtn->setText(tr("Создать задачу"));
    addTaskBtn->setFlat(true);
    addTaskBtn->setIconSize(QSize{24, 24});

    addSubtaskBtn = new QPushButton;
    addSubtaskBtn->setIcon(QPixmap(":/Resources/add_subobject.png"));
    addSubtaskBtn->setText(tr("Создать подзадачу"));
    addSubtaskBtn->setFlat(true);
    addSubtaskBtn->setIconSize(QSize{24, 24});

    editTaskBtn = new QPushButton;
    editTaskBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editTaskBtn->setText(tr("Редактировать"));
    editTaskBtn->setFlat(true);
    editTaskBtn->setIconSize(QSize{24, 24});

    removeTaskBtn = new QPushButton;
    removeTaskBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeTaskBtn->setText(tr("Удалить"));
    removeTaskBtn->setFlat(true);
    removeTaskBtn->setIconSize(QSize{24, 24});

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


    detailsCommentBtn = new QPushButton;
    detailsCommentBtn->setIcon(QPixmap(":/Resources/show_object.png"));
    detailsCommentBtn->setText(tr("Подробности"));
    detailsCommentBtn->setFlat(true);
    detailsCommentBtn->setIconSize(QSize{24, 24});

    addCommentBtn = new QPushButton;
    addCommentBtn->setIcon(QPixmap(":/Resources/add_object.png"));
    addCommentBtn->setText(tr("Добавить комментарий"));
    addCommentBtn->setFlat(true);
    addCommentBtn->setIconSize(QSize{24, 24});

    addSubcommentBtn = new QPushButton;
    addSubcommentBtn->setIcon(QPixmap(":/Resources/add_subobject.png"));
    addSubcommentBtn->setText(tr("Ответить"));
    addSubcommentBtn->setFlat(true);
    addSubcommentBtn->setIconSize(QSize{24, 24});

    editCommentBtn = new QPushButton;
    editCommentBtn->setIcon(QPixmap(":/Resources/edit_object.png"));
    editCommentBtn->setText(tr("Редактировать"));
    editCommentBtn->setFlat(true);
    editCommentBtn->setIconSize(QSize{24, 24});

    removeCommentBtn = new QPushButton;
    removeCommentBtn->setIcon(QPixmap(":/Resources/remove_object.png"));
    removeCommentBtn->setText(tr("Удалить"));
    removeCommentBtn->setFlat(true);
    removeCommentBtn->setIconSize(QSize{24, 24});

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


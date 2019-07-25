#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QToolBar>

MainWindow::MainWindow(Db *db, QWidget * parent) :
    QMainWindow(parent), db(db)
{
    QString title = "Программа \"Распоряжения\" | " + db->getCurrentUser().getFio() + " (" + db->getCurrentUser().getPosition().getTitle() + ")";
    setWindowTitle(tr(title.toStdString().c_str()));

    setupGui();

    showMaximized();
}

void MainWindow::setupGui()
{
    QWidget * wgt = new QWidget(this);
    setCentralWidget(wgt);

    QToolBar* tb = new QToolBar("Панель инструментов окна");
    tb->addAction(QPixmap(":/Resources/report_icon.png"), "Отчет", this, SLOT(slotNoImpl()));
    tb->addAction(QPixmap(":/Resources/users_icon.png"), "Пользователи", this, SLOT(slotNoImpl()));
    tb->addAction(QPixmap(":/Resources/status_sequence_icon.png"), "Бизнес-процесс", this, SLOT(slotNoImpl()));
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tb->addWidget(spacer);
    tb->addAction(QPixmap(":/Resources/about_icon.png"), "О программе", this, SLOT(slotNoImpl()));

    addToolBar(Qt::TopToolBarArea, tb);
}



MainWindow::~MainWindow()
{
    delete db;
}


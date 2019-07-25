#include "mainwindow.h"


MainWindow::MainWindow(Db *db, QWidget * parent) :
    QMainWindow(parent), db(db)
{
    setWindowTitle("Программа \"Распоряжения\" | Кабинет " + db->getCurrentUser().getFio());
}

void MainWindow::setupGui()
{

}



MainWindow::~MainWindow()
{
    delete db;
}


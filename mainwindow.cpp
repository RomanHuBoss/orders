#include "mainwindow.h"


MainWindow::MainWindow(Db *db, QWidget * parent) :
    QMainWindow(parent), db(db)
{

}



MainWindow::~MainWindow()
{
    delete db;
}


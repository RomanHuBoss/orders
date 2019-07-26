#ifndef PROJECTDETAILSDIALOG_H
#define PROJECTDETAILSDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include "utilities.h"
#include "db.h"

class ProjectDialog : public QDialog
{
    Q_OBJECT
private:
    DIALOG_ACTIONS action;
    Db * db;
    int id;
    QLineEdit * ledTitle;
    QTextEdit * tedDescription;
    QDateEdit * dedStartDate;
    QDateEdit * dedEndDate;

    QPushButton * btnSave;
public:
    ProjectDialog(const RowData& row, DIALOG_ACTIONS action, Db* db, QWidget *parent = nullptr);

signals:
    void raiseDataChanged();
public slots:

private slots:
    void onSaveForm();
};

#endif // PROJECTDETAILSDIALOG_H

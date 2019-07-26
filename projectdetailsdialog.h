#ifndef PROJECTDETAILSDIALOG_H
#define PROJECTDETAILSDIALOG_H

#include <QDialog>
#include "utilities.h"

class ProjectDetailsDialog : public QDialog
{
    Q_OBJECT
public:
    ProjectDetailsDialog(const RowData& row, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PROJECTDETAILSDIALOG_H

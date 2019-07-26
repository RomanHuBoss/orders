#include "projectdetailsdialog.h"

#include <QFormLayout>
#include <QLabel>

ProjectDetailsDialog::ProjectDetailsDialog(const RowData& row, QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Данные проекта"));

    QFormLayout * layout = new QFormLayout;
    setLayout(layout);
    setModal(true);
    setFixedSize(800, 600);

    layout->addRow(new QLabel(tr("Название: ")), new QLabel(row["title"].toString()));
    layout->addRow(new QLabel(tr("Описание: ")), new QLabel(row["description"].toString()));
}

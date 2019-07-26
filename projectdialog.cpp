#include "projectdialog.h"

#include <QFormLayout>
#include <QLabel>
#include <QDate>
#include <QVBoxLayout>
#include <QGroupBox>

ProjectDialog::ProjectDialog(const RowData& row, DIALOG_ACTIONS action, Db *db, QWidget *parent) :
    QDialog(parent), action(action), db(db), id(-1)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout * vboxLayout = new QVBoxLayout;
    setLayout(vboxLayout);
    setModal(true);
    setFixedSize(500, 400);

    QFormLayout * formLayout = new QFormLayout;
    vboxLayout->addLayout(formLayout);

    ledTitle = new QLineEdit;
    dedStartDate = new QDateEdit;
    dedStartDate = new QDateEdit;
    dedEndDate = new QDateEdit;
    tedDescription = new QTextEdit;
    dedStartDate->setDate(QDate::currentDate());
    dedEndDate->setDate(QDate::currentDate());

    if (action == SHOW) {
        setWindowTitle(tr("Данные проекта"));
        ledTitle->setText(row["title"].toString());
        dedStartDate->setDate(row["start_date"].toDate());
        dedEndDate->setDate(row["end_date"].toDate());
        tedDescription->setText(row["description"].toString());
    }
    else if (action == ADD) {
        setWindowTitle(tr("Создание проекта"));
    }
    else if (action == EDIT) {
        id = row["id"].toInt();
        setWindowTitle(tr("Редактирование проекта"));

        ledTitle->setText(row["title"].toString());
        if (!row["start_date"].isNull()) {
            dedStartDate->setDate(row["start_date"].toDate());
        }
        if (!row["end_date"].isNull()) {
            dedEndDate->setDate(row["end_date"].toDate());
        }
        tedDescription->setText(row["description"].toString());
    }

    formLayout->addRow(new QLabel(tr("Название: ")), ledTitle);
    formLayout->addRow(new QLabel(tr("Начало: ")), dedStartDate);
    formLayout->addRow(new QLabel(tr("Завершение: ")), dedEndDate);

    QGroupBox * groupbox = new QGroupBox("Описание проекта");
    QVBoxLayout * groupboxVLayout = new QVBoxLayout;
    groupbox->setLayout(groupboxVLayout);
    groupboxVLayout->addWidget(tedDescription);

    vboxLayout->addWidget(groupbox);

    if (action == ADD || action == EDIT) {
        btnSave = new QPushButton("Сохранить");
        connect(btnSave, SIGNAL(clicked()), this, SLOT(onSaveForm()));

        QHBoxLayout * hboxLayout = new QHBoxLayout;
        hboxLayout->addStretch(1);
        hboxLayout->addWidget(btnSave);
        vboxLayout->addLayout(hboxLayout);
    }
    else {
        ledTitle->setDisabled(true);
        dedStartDate->setDisabled(true);
        dedEndDate->setDisabled(true);
        tedDescription->setDisabled(true);
    }

}

void ProjectDialog::onSaveForm() {
    RowData data;

    data["id"] = id;
    data["title"] = ledTitle->text();
    data["description"] = tedDescription->toPlainText();
    data["start_date"] = dedStartDate->date();
    data["end_date"] = dedEndDate->date();

    if (db->saveProjectData(data, action)) {
        emit raiseDataChanged();
        close();
    }

}

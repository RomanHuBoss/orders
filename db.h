#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QSqlDatabase>
#include "user.h"
#include "utilities.h"


class Db
{
    QSqlDatabase db;
    User currentUser;
public:
    Db();
    ~Db();
    bool connect();
    bool tryLogin(const QString &login, const QString &password);
    QString lastError() const;
    User getUserByLoginPassword(const QString &login, const QString &password);
    const User& getCurrentUser() const;
    Rows getProjectsData() const;
    Rows getTasksData(int id_project) const;
    Rows getCommentsData(int id_task) const;

    bool saveProjectData(const RowData& row, DIALOG_ACTIONS action) const;
    bool removeProject(const RowData& row) const;
    bool removeTask(const RowData& row) const;
};

#endif // DB_H

#include "db.h"
#include <QSqlError>
#include <QStringList>
#include <QMessageBox>
#include <QSqlQuery>
#include "userposition.h"

Db::Db()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("orders");
    db.setUserName("postgres");
    db.setPassword("postgres");
}

Db::~Db()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool Db::connect()
{
    bool ok = db.open();

    if (!ok) {
        db.close();
        return false;
    }

    return true;
}

bool Db::tryLogin(const QString &login, const QString &password)
{
    currentUser = getUserByLoginPassword(login,password);
    return currentUser.isValid();
}

QString Db::lastError() const {
    return db.lastError().text();
}


User Db::getUserByLoginPassword(const QString &login, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT w.*, p.id as id_position, p.title as position_title, p.description as position_description,"
                  "p.is_head as  is_head FROM department_workers as w LEFT JOIN positions as p ON p.id = w.id_position  "
                  "WHERE w.login = :login AND w.password = md5(:password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();

    if (query.size() == 0) {
        return User();
    }

    query.first();

    UserPosition position(query.value("id_position").toInt(),
                          query.value("position_title").toString(),
                          query.value("position_description").toString(),
                          query.value("is_head").toBool()
                          );

    return User(query.value("id").toInt(),
                query.value("fio").toString(),
                login,
                position
                );
}

const User &Db::getCurrentUser() const
{
    return currentUser;
}

Rows Db::getProjectsData() const
{
    Rows result;

    QSqlQuery query;
    query.prepare("SELECT * FROM projects ORDER BY start_date, title");
    query.exec();

    if (query.size() == 0) {
        return result;
    }

    while (query.next()) {
        RowData row;
        row["id"] = query.value("id");
        row["title"] = query.value("title");
        row["description"] = query.value("description");
        row["creation_dt"] = query.value("creation_dt");
        row["start_date"] = query.value("start_date");
        row["end_date"] = query.value("end_date");
        result.push_back(row);
    }

    return result;
}

Rows Db::getTasksData(int id_project) const
{
    Rows result;

    QSqlQuery query;
    query.prepare("SELECT DISTINCT ON (t.id) "
                  "t.id, t.pid, t.id_project, t.id_worker, t.title, t.description, t.deadline_dt, t.published_dt, "
                  "s.id as id_status, s.title as status_title, "
                  "w.fio"
                  "FROM tasks as t "
                  "LEFT JOIN tasks_statuses_history as h ON h.id_task = t.id "
                  "LEFT JOIN statuses as s ON h.id_status = s.id"
                  "LEFT JOIN department_workers as w ON w.id = t.id_worker"
                  "ORDER BY h.status_dt DESC");
    query.bindValue(":id_project", id_project);
    query.exec();

    if (query.size() == 0) {
        return result;
    }


    while (query.next()) {
        RowData row;
        row["id"] = query.value("id");
        row["pid"] = query.value("pid");
        row["id_project"] = query.value("id_project");
        row["id_worker"] = query.value("id_worker");
        row["title"] = query.value("title");
        row["description"] = query.value("description");
        row["deadline_dt"] = query.value("published_dt");
        row["id_status"] = query.value("id_status");
        row["status_title"] = query.value("status_title");
        row["fio"] = query.value("fio");
        result.push_back(row);
    }

    return result;
}

Rows Db::getCommentsData(int id_task) const
{
    Rows result;

    return result;
}

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

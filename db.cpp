#include "db.h"
#include <QSqlError>
#include <QStringList>
#include <QMessageBox>
#include <QSqlQuery>

Db::Db()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("orders");
    db.setUserName("admin");
    db.setPassword("admin");
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
    query.prepare("SELECT * FROM department_workers WHERE login = :login AND password = md5(:password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();

    if (query.size() == 0) {
        return User();
    }

    query.first();

    return User(query.value("id").toInt(),
                query.value("fio").toString(),
                query.value("is_head").toBool(),
                login
                );
}

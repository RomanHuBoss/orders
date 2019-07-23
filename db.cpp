#include "db.h"
#include <QSqlError>

Db::Db()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("orders");
    db.setUserName("admin");
    db.setPassword("admin");
}

bool Db::connect()
{
    bool ok = db.open();

    if (!ok) {
        return false;
    }

    return true;
}

QString Db::lastError() const {
    return db.lastError().text();
}

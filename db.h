#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QSqlDatabase>
#include "user.h"

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
};

#endif // DB_H

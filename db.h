#ifndef DB_H
#define DB_H

#include <QSqlDatabase>

class Db
{
    QSqlDatabase db;
public:
    Db();
    bool connect();
    QString lastError() const;
};

#endif // DB_H

#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <QString>
#include <QVariant>
#include "userposition.h"

class User
{
private:
    int id;
    QString fio;
    QString login;
    UserPosition position;
    QString password;
public:
    User();
    User(int id, const QString& fio, const QString& login, const UserPosition& position);
    User(const QMap<QString, QVariant> props);

    int getId() const;
    const QString& getFio() const;
    const UserPosition& getPosition() const;
    const QString& getLogin() const;
    const QString& getPassword() const;
    bool isValid() const;

};

#endif // CURRENTUSER_H

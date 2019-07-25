#include "user.h"

Q_DECLARE_METATYPE(UserPosition);

User::User() :
    id(0), position(UserPosition())
{    
}

User::User(int id, const QString &fio, const QString &login, const UserPosition& position) :
    id(id), fio(fio), login(login), position(position)
{

}

User::User(const QMap<QString, QVariant> props)
{
    if (props.contains("id")) {
        id = props["id"].toInt();
    }

    if (props.contains("fio")) {
        fio = props["fio"].toString();
    }

    if (props.contains("login")) {
        login = props["login"].toString();
    }

    if (props.contains("position")) {
        position = props["position"].value<UserPosition>();
    }

}

int User::getId() const
{
    return id;
}

const QString &User::getFio() const
{
    return fio;
}

const QString &User::getLogin() const
{
    return login;
}

const UserPosition& User::getPosition() const {
    return position;
}

const QString &User::getPassword() const
{
    return password;
}

bool User::isValid() const
{
    return id > 0;
}

bool User::isHead() const
{
    return position.isHead();
}

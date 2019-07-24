#include "user.h"

User::User()
{

}

User::User(int id, const QString &fio, bool is_head, const QString &login) :
    id(id), fio(fio), is_head(is_head), login(login)
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

    if (props.contains("is_head")) {
        is_head = props["is_head"].toBool();
    }

    if (props.contains("login")) {
        login = props["login"].toString();
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

bool User::isHead() const
{
    return is_head;
}

const QString &User::getLogin() const
{
    return login;
}

const QString &User::getPassword() const
{
    return password;
}

bool User::isValid() const
{
    return id > 0;
}

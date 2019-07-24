#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <QString>
#include <QVariant>

class User
{
private:
    int id;
    QString fio;
    bool is_head;
    QString login;
    QString password;
public:
    User();
    User(int id, const QString& fio, bool is_head, const QString& login);
    User(const QMap<QString, QVariant> props);

    int getId() const;
    const QString& getFio() const;
    bool isHead() const;
    const QString& getLogin() const;
    const QString& getPassword() const;
    bool isValid() const;

};

#endif // CURRENTUSER_H

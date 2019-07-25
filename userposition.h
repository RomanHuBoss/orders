#ifndef USERPOSITION_H
#define USERPOSITION_H

#include <QString>

class UserPosition
{
    int id;
    QString title;
    QString description;
    bool is_head;
public:
    UserPosition();
    UserPosition(int id, const QString& title, const QString& description, bool is_head);
    int getId() const;
    const QString& getTitle() const;
    const QString& getDescription() const;
    bool isHead() const;
    bool isValid() const;
};

#endif // USERPOSITION_H

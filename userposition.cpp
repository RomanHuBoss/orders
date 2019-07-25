#include "userposition.h"

UserPosition::UserPosition() :
    id(0), is_head(false)
{

}

UserPosition::UserPosition(int id, const QString &title, const QString &description, bool is_head) :
    id(id), title(title), description(description), is_head(is_head)
{

}

int UserPosition::getId() const
{
    return id;
}

const QString &UserPosition::getTitle() const
{
    return title;
}

bool UserPosition::isValid() const {
    return id > 0;
}

const QString &UserPosition::getDescription() const
{
    return description;
}

bool UserPosition::isHead() const
{
    return is_head;
}

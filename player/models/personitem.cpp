#include <QString>
#include <QObject>

#include "personitem.h"

using namespace GluonPlayer;

class PersonItem::Private
{
    public:
        Private()
        {
        }

        QString id;
        QString firstname;
        QString lastname;
        bool isFriend;
};

//if no friendship is specified, let's assume this object is not a friend of the user
PersonItem::PersonItem( const QString& id, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->firstname = "";
    d->lastname = "";
    d->isFriend = false;
}

//if no friendship is specified, let's assume this object is not a friend of the user
PersonItem::PersonItem( const QString& id, const QString& firstname, const QString& lastname, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->firstname = firstname;
    d->lastname = lastname;
    d->isFriend = false;
}

PersonItem::PersonItem( const QString& id, const QString& firstname, const QString& lastname, bool isFriend, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->firstname = firstname;
    d->lastname = lastname;
    d->isFriend = isFriend;
}

PersonItem::~PersonItem()
{
    delete d;
}

QString PersonItem::id() const
{
    return d->id;
}

QString PersonItem::firstname() const
{
    return d->firstname;
}

QString PersonItem::lastname() const
{
    return d->lastname;
}

bool PersonItem::isFriend()
{
    return d->isFriend;
}

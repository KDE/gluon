#include <QString>
#include <QObject>

#include "activityitem.h"

using namespace GluonPlayer;

class ActivityItem::Private
{
    public:
        Private()
        {
        }

        QString id;
        QString firstname;
        QString lastname;
};

//if no friendship is specified, let's assume this object is not a friend of the user
ActivityItem::ActivityItem( const QString& id, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->firstname = "";
    d->lastname = "";
}

//if no friendship is specified, let's assume this object is not a friend of the user
ActivityItem::ActivityItem( const QString& id, const QString& firstname, const QString& lastname, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->firstname = firstname;
    d->lastname = lastname;
}

ActivityItem::~ActivityItem()
{
    delete d;
}

QString ActivityItem::id() const
{
    return d->id;
}

QString ActivityItem::firstname() const
{
    return d->firstname;
}

QString ActivityItem::lastname() const
{
    return d->lastname;
}

#ifndef GLUONPLAYER_ACTIVITYITEM_H
#define GLUONPLAYER_ACTIVITYITEM_H

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QString>
#include <QtCore/QObject>

namespace GluonPlayer
{
    class ActivityItem : public QObject
    {
            Q_OBJECT
        public:
            ActivityItem( const QString& id, QObject* parent = 0);
            ActivityItem( const QString& id, const QString& firstname, const QString& lastname, QObject* parent = 0 );
            virtual ~ActivityItem();

            QString id() const;
            QString firstname() const;
            QString lastname() const;

        private:
            class Private;
            Private* const d;
    };
    
}

#endif //GLUONPLAYER_ActivityItem_H
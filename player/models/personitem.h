#ifndef GLUONPLAYER_PERSONITEM_H
#define GLUONPLAYER_PERSONITEM_H

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QString>
#include <QtCore/QObject>

namespace GluonPlayer
{
    class PersonItem : public QObject
    {
            Q_OBJECT
        public:
            PersonItem( const QString& id, const QString& firstname, const QString& lastname, QObject* parent = 0 );
            PersonItem( const QString& id, const QString& firstname, const QString& lastname, bool isFriend, QObject* parent );
            virtual ~PersonItem();

            QString id() const;
            QString firstname() const;
            QString lastname() const;
            bool isFriend();

        private:
            class Private;
            Private* const d;
    };
    
}

#endif //GLUONPLAYER_PERSONITEM_H
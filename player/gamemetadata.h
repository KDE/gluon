/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <shaan7in@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef GLUONPLAYER_GAMEMETADATA_H
#define GLUONPLAYER_GAMEMETADATA_H
 
#include <QtCore/QObject>
 
namespace GluonPlayer
{
    class GameMetadata : public QObject
    {
            Q_OBJECT
            Q_PROPERTY( QString gameId READ gameId WRITE setGameId NOTIFY gameIdChanged )
            Q_PROPERTY( QString gameName READ gameName NOTIFY gameNameChanged )
            Q_PROPERTY( QString gameDescription READ gameDescription NOTIFY gameDescriptionChanged )
            Q_PROPERTY( QString gameChangelog READ gameChangelog NOTIFY gameChangelogChanged )
            Q_PROPERTY( QString gameSummary READ gameSummary NOTIFY gameSummaryChanged )
            Q_PROPERTY( QString gameVersion READ gameVersion NOTIFY gameVersionChanged )
            Q_PROPERTY( QString gamePreviewPicture READ gamePreviewPicture NOTIFY gamePreviewPictureChanged )
            Q_PROPERTY( QString gameRating READ gameRating NOTIFY gameRatingChanged )
 
        public:
            explicit GameMetadata( QObject* parent = 0 );
            virtual ~GameMetadata();
 
            QString gameId() const;
            void setGameId( const QString& gameId );
 
            QString gameName() const;
            QString gameDescription() const;
            QString gameChangelog() const;
            QString gameSummary() const;
            QString gameVersion() const;
            QString gamePreviewPicture() const;
            QString gameRating() const;
 
        signals:
            void gameIdChanged();
            void gameNameChanged();
            void gameDescriptionChanged();
            void gameChangelogChanged();
            void gameSummaryChanged();
            void gameVersionChanged();
            void gamePreviewPictureChanged();
            void gameRatingChanged();
 
        private:
            class Private;
            Private* const d;
    };
 
}
 
#endif // GLUONPLAYER_GAMEMETADATA_H

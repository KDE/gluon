/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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
 
#ifndef GLUON_PLAYER_HIGHSCORESMODEL_H
#define GLUON_PLAYER_HIGHSCORESMODEL_H
 
#include "../gluon_player_export.h"
 
#include <QtCore/QAbstractTableModel>
 
namespace GluonCore
{
    class GluonObject;
};
 
namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT HighScoresModel : public QAbstractTableModel
    {
            Q_OBJECT
        public:
            /**
             * @param gameId The game ID which will be used to perform the lookup of the online
             * service
             */
            explicit HighScoresModel( QString gameId, QObject* parent = 0 );
            virtual ~HighScoresModel();
 
            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
            Qt::ItemFlags flags( const QModelIndex& index ) const;
 
            enum Column
            {
                NameColumn,
                HighScoreColumn,
                LevelColumn,
            };
 
        private:
            void loadData();
            void saveData();
 
            class Private;
            Private* const d;
    };
 
}
 
#endif // GLUON_PLAYER_HIGHSCORESMODEL_H
 
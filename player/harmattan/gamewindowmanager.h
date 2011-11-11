/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010-2011 Laszlo Papp <lpapp@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GLUON_PLAYER_HARMATTAN_GAMEWINDOWMANAGER_H
#define GLUON_PLAYER_HARMATTAN_GAMEWINDOWMANAGER_H

#include "lib/models/achievementsmodel.h"
#include "lib/models/gameitemsmodel.h"
#include "lib/models/commentitemsmodel.h"

#include <core/gluon_global.h>
#include <graphics/engine.h>
#include <graphics/renderwidget.h>
#include <engine/game.h>
#include <engine/gameproject.h>

#include <QtCore/QModelIndex>

namespace GluonHarmattanPlayer
{
    class GameWindowManager: public QObject
    {
            Q_OBJECT
        public:
            explicit GameWindowManager( const QString& fileName = "" );
            virtual ~GameWindowManager();

            bool isViewportGLWidget();
            Q_INVOKABLE void setProject( int index );
            Q_INVOKABLE int availableGamesCount( ) const;
            Q_INVOKABLE void buildCommentsModel( int index );

            GluonPlayer::AchievementsModel* achievementsModel() const;
            void setAchievementsModel( GluonPlayer::AchievementsModel* achievementsModel );

            GluonPlayer::GameItemsModel* gameItemsModel() const;
            void setGameItemsModel( GluonPlayer::GameItemsModel* gameItemsModel );

            GluonPlayer::CommentItemsModel* commentItemsModel() const;
            void setCommentItemsModel( GluonPlayer::CommentItemsModel* commentItemsModel );

            void show();

        public slots:
            void startGame();
            void pauseGame();
            void stopGame();

        private slots:
            void openProject();
            void setProject( const QModelIndex& index );
            void activated( QModelIndex index );
            void countFrames( int );
            void updateTitle( int msec );

        private:

            class GameWindowManagerPrivate;
            GameWindowManagerPrivate* d;

            QString m_projectFilePath;
            GluonEngine::GameProject* m_project;

            int m_viewportWidth;
            int m_viewportHeight;
    };
}

#endif // GLUON_PLAYER_HARMATTAN_MAINWINDOW_H


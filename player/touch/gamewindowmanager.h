/*****************************************************************************
 * This file is part of the Gluon Development Platform                       *
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us                      *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License along   *
 * with this program; if not, write to the Free Software Foundation, Inc.,   *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
 *****************************************************************************/

#ifndef GLUONKDEPLAYER_MAINWINDOW_H
#define GLUONKDEPLAYER_MAINWINDOW_H

#include "lib/models/gameitemsmodel.h"
#include "lib/models/commentitemsmodel.h"

#include "core/gluon_global.h"
#include "graphics/engine.h"
#include "graphics/renderwidget.h"
#include "engine/game.h"
#include "engine/gameproject.h"

#include <QtOpenGL/QGLWidget>
#include <QtGui/QGraphicsView>
#include <QtCore/QModelIndex>

namespace GluonQMLPlayer {
    /**
     * The main window of the KDE Player frontend
     */
    class GameWindowManager: public QObject
    {
        Q_OBJECT
        public:
            explicit GameWindowManager( GluonGraphics::RenderWidget* renderWidget,
                    QGraphicsView* view, GluonPlayer::GameItemsModel* gameItemsModel, const QString& fileName = "" );
            explicit GameWindowManager( const QString& fileName = "" );
            virtual ~GameWindowManager();

            bool isViewportGLWidget();
            Q_INVOKABLE void setProject( int index );
            Q_INVOKABLE int availableGamesCount( ) const;
            Q_INVOKABLE void buildCommentsModel( int index );

            GluonPlayer::GameItemsModel* gameItemsModel() const;
            void setGameItemsModel(GluonPlayer::GameItemsModel* gameItemsModel);

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

            QString m_gameFileName;
            GluonEngine::GameProject* m_project;

            QGraphicsView* m_view;
            GluonPlayer::GameItemsModel* m_gameItemsModel;

            GluonPlayer::CommentItemsModel* m_commentsModel;

            int m_viewportWidth;
            int m_viewportHeight;
    };
}

#endif // GLUONKDEPLAYER_MAINWINDOW_H


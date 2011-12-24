/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Shantanu Tushar <shaan7in@gmail.com>
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

#ifndef PLASMAAPPLET_H
#define PLASMAAPPLET_H

#include "glfboapplet.h"

#include <QtCore/QModelIndex>

class QGraphicsLinearLayout;

namespace GluonGraphics
{
    class RenderWidget;
}

namespace GluonEngine
{
    class GameProject;
}

class GamesOverlay;
class GameDetailsOverlay;

namespace GluonPlayer
{
    class GameItemsModel;

    class PlasmaApplet : public Plasma::Applet
    {
            Q_OBJECT

        public:
            PlasmaApplet( QObject* parent, const QVariantList& args );
            virtual ~PlasmaApplet();
            void init();

            virtual void paintInterface( QPainter* painter, const QStyleOptionGraphicsItem* option, const QRect& contentsRect );

        private:
            int m_viewportWidth;
            int m_viewportHeight;
            QString m_gameFileName;
            GluonEngine::GameProject* m_project;
            GameItemsModel* m_gameItemsModel;
            GamesOverlay* m_gamesOverlay;
            GameDetailsOverlay* m_gameDetailsOverlay;
            QGraphicsLinearLayout* m_layout;
            GluonGraphics::RenderWidget* m_renderer;

        protected:
            void resizeEvent( QGraphicsSceneResizeEvent* event );

        protected slots:
            void openProject();
            void setProject( const QModelIndex& index );
            void doPaint();
            void startGame();
            void showGames();
            void showGameDetails( const QModelIndex& index );
    };
}

K_EXPORT_PLASMA_APPLET( gluonplayer, GluonPlayer::PlasmaApplet )

#endif // PLASMAAPPLET_H

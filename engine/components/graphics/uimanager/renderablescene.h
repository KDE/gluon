/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#ifndef RENDERABLESCENE_H
#define RENDERABLESCENE_H

#include <QtGui/QGraphicsScene>
#include <QtCore/QEvent>

class QGLFramebufferObject;

namespace GluonEngine
{
    class RenderableScene : public QGraphicsScene
    {
        Q_OBJECT
        public:
            RenderableScene( QObject* parent = 0 );
            ~RenderableScene();

            void renderScene();

        protected:
            void drawBackground(QPainter* painter, const QRectF& rect);

        private slots:
            void deliverEvent(QEvent* event);

        private:
            class RenderableScenePrivate;
            RenderableScenePrivate* const d;

            Q_PRIVATE_SLOT( d, void repaintNeeded() );
            Q_PRIVATE_SLOT( d, void newViewport( Viewport* viewport ) );
            Q_PRIVATE_SLOT( d, void viewportSizeChanged( int left, int bottom, int width, int height ) );
    };

}

#endif

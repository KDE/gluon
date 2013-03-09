/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef QTQUICKRENDERTARGET_H
#define QTQUICKRENDERTARGET_H

#include "renderchainitem.h"
#include "texture.h"

class QDeclarativeContext;
namespace GluonGraphics
{
    class QtQuickRenderer : public Texture, public RenderChainItem
    {
            Q_OBJECT
        public:
            explicit QtQuickRenderer( QObject* parent = 0 );
            virtual ~QtQuickRenderer();

            virtual void update();
            virtual void renderContents();

            virtual bool load( const QUrl& url );
            virtual QImage image() const;
            virtual TextureData* data() const;

            QDeclarativeContext* context() const;

            virtual void resize( int width, int height );

        public Q_SLOTS:
            void deliverEvent( QEvent* event );

        private:
            class Private;
            Private* const d;
    };
}

Q_DECLARE_METATYPE( GluonGraphics::QtQuickRenderer* );

#endif // QTQUICKRENDERTARGET_H

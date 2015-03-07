/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2015 Felix Rohrbach <kde@fxrh.de>
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

#include "gluon_graphics_export.h"

class QQmlContext;
class QQuickRenderControl;
class QQuickWindow;
namespace GluonGraphics
{
    /**
     * A class providing a rendered version of a QtQuick scene. This is the abstract
     * class - use Backend::createQuickRenderer to get an instance.
     *
     * QtQuickRender provides the scene as texture as well as renders it to screen.
     *
     * For Implementations, you need to at least implement renderQuick (which renders the
     * quick scene to texture data) and data (which returns that texture data), but
     * you might want to customize resize and startQuick, too.
     */
    class GLUON_GRAPHICS_EXPORT QtQuickRenderer : public Texture, public RenderChainItem
    {
            Q_OBJECT
        public:
            explicit QtQuickRenderer( QObject* parent = 0 );
            virtual ~QtQuickRenderer();

            virtual void renderContents();

            virtual void load( const QUrl& url );

            /**
             * return an Image of the current szene
             */
            virtual QImage image() const;

            virtual TextureData* data() const=0;

            virtual QQmlContext* context() const;

            virtual void resize( int width, int height );

        public Q_SLOTS:
            /**
             * Create an event in the quick scene (e.g. a mouse click).
             */
            virtual void deliverEvent( QEvent* event );

            /**
             * Request a re-rendering of the scene.
             */
            void requestUpdate();

        protected:
            /**
             * Render the scene to texture data. You don't need to care about
             * updating the scene here.
             */
            virtual void renderQuick()=0;

            int width();
            int height();
            QQuickWindow* quickWindow();
            QQuickRenderControl* renderControl();
            bool quickLoaded();
            bool quickInitialized();
            bool needsUpdating();

        protected Q_SLOTS:
            /**
             * Called after the QML file was loaded and initializes the scene.
             * Returns true, if the loading and initialisation was successfull,
             * false otherwise.
             */
            virtual bool startQuick();

        private:
            class Private;
            Private* d;
    };
}

Q_DECLARE_METATYPE( GluonGraphics::QtQuickRenderer* );

#endif // QTQUICKRENDERTARGET_H

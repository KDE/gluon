/*****************************************************************************
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

#ifndef GLUONGRAPHICS_BACKEND_H
#define GLUONGRAPHICS_BACKEND_H

#include <QtCore/QObject>
#include <QtCore/QtPlugin>

class QWindow;
namespace GluonGraphics
{
    class Shader;
    class TextureData;
    class Buffer;
    class OutputSurface;
    class RenderTarget;
    class MeshData;

    /**
     * \brief Abstract class for encapsulating all graphics backend details.
     *
     * This class primarily acts as a factory for creating platform-specific
     * instances of basic graphics objects.
     */
    class Backend : public QObject
    {
        public:
            enum InformationLevel
            {
                SummaryInformation,
                FullInformation,
                VerboseInformation
            };

            /**
             * Constructor.
             */
            Backend() { }
            /**
             * Destructor.
             */
            virtual ~Backend() { }

            /**
             * Initialize the backend.
             *
             * \param widget A widget that can be used during initialization.
             *
             * \return true when successfully initialized, false if not.
             */
            virtual bool initialize( QWindow* window ) = 0;

            /**
             * A description of the last error that occurred.
             */
            virtual QString errorString() = 0;

            /**
             * Returns a string to identify the backend with.
             */
            virtual QString identifier() = 0;

            /**
             * Returns a string with information about the backend.
             *
             * \param level The amount of information requested.
             */
            virtual QString information( InformationLevel level ) = 0;

            /**
             * Create a Shader object.
             *
             * \return A platform-specific implementation of a Shader object.
             */
            virtual Shader* createShader() = 0;
            /**
             * Create a Texture object.
             *
             * \return A platform-specific implementation of a Texture object.
             */
            virtual TextureData* createTextureData() = 0;
            /**
             * Create a Buffer object.
             *
             * \return A platform-specific implementation of a Buffer object.
             */
            virtual Buffer* createBuffer() = 0;
            /**
             * Create a RenderTarget object.
             *
             * \return A platform-specific implementation of a RenderTarget object.
             */
            virtual RenderTarget* createRenderTarget() = 0;
            /**
             * Create an OutputSurface object.
             *
             * \return A platform-specific implementation of an OutputSurface object.
             */
            virtual OutputSurface* createOutputSurface( QWindow* widget ) = 0;

            virtual MeshData* createMeshData() = 0;
    };

}

Q_DECLARE_INTERFACE( GluonGraphics::Backend, "org.kde.gluon.graphics.backend" );

#define GLUONGRAPHICS_BACKENDPLUGIN \
    Q_INTERFACES( GluonGraphics::Backend )\
    Q_PLUGIN_METADATA( IID "org.kde.gluon.graphics.backend" )

#endif // GLUONGRAPHICS_BACKEND_H

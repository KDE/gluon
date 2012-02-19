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

namespace GluonGraphics
{
    class Shader;
    class TextureData;
    class Buffer;
    class OutputSurface;

    /**
     * \brief Abstract class for encapsulating all graphics backend details.
     *
     * This class primarily acts as a factory for creating platform-specific
     * instances of basic abstracted objects.
     */
    class Backend
    {
        public:
            /**
             * Constructor.
             */
            Backend() { }
            /**
             * Destructor.
             */
            virtual ~Backend() { }

            /**
             * Create a Shader object.
             *
             * \return A platform-specific implementation of a Shader object.
             */
            virtual Shader* createShader() = 0;
            /**
             * Create a TextureData object.
             *
             * \return A platform-specific implementation of a TextureData object.
             */
            virtual TextureData* createTextureData() = 0;
            /**
             * Create a Buffer object.
             *
             * \return A platform-specific implementation of a Buffer object.
             */
            virtual Buffer* createBuffer() = 0;
            /**
             * Create an OutputSurface object.
             *
             * \return A platform-specific implementation of an OutputSurface object.
             */
            virtual OutputSurface* createOutputSurface() = 0;
    };

}

#endif // GLUONGRAPHICS_BACKEND_H

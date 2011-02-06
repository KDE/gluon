/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

// WILL BE REPLACE BY QGLTexture!!!!!!!!

#ifndef GLUON_GRAPHICS_TEXTURE_H
#define GLUON_GRAPHICS_TEXTURE_H

#include "gluon_graphics_export.h"
#include <QtCore/QObject>

class QImage;
class QUrl;
namespace GluonGraphics
{
    /**
     * \brief A graphic used to give an item more surface detail.
     *
     * A texture is quasi-repetitious pattern of a defined size,
     * used to convey the coloration, shading, and the surface
     * imperfections of a three dimensional polygon.
     *
     * This class provides the necessary functionality to work with
     * textures. It is mainly used as a data source for materials.
     *
     * \see Material
     *
     * \todo Add support for multi-dimensional textures and other
     * non-2D textures.
     */
    class GLUON_GRAPHICS_EXPORT Texture : public QObject
    {
            Q_OBJECT
        public:
            explicit Texture( QObject* parent = 0 );
            virtual ~Texture();

            /**
             * Load the data for this texture from a file.
             *
             * \param url The url of the file to load the data from.
             *
             * \return True if successful, false if not.
             */
            bool load( const QUrl& url );

            /**
             * Retrieve the OpenGL texture id.
             *
             * \return The OpenGL texture ID for this texture.
             */
            uint glTexture() const;
            
            /**
             * Retrieve the image used for this texture.
             * 
             * \return The image used.
             */
            QImage image() const;

        private:
            class TexturePrivate;
            TexturePrivate* const d;
    };
}

#endif // GLUON_GRAPHICS_TEXTURE_H

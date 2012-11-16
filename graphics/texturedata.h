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

#ifndef GLUONGRAPHICS_TEXTUREDATA_H
#define GLUONGRAPHICS_TEXTUREDATA_H

namespace GluonGraphics
{
    class TextureData
    {
        public:
            enum FilteringMode
            {
                UnknownFilteringMode,
                NearestFilteringMode,
                BilinearFilteringMode,
                TrilinearFilteringMode
            };

            TextureData() { }
            virtual ~TextureData() { }

            virtual void bind( unsigned int unit ) = 0;
            virtual void release() = 0;

            virtual void setData( int width, int height, void* data ) = 0;
            virtual void setFilteringMode( FilteringMode mode ) = 0;
    };
}

#endif // GLUONGRAPHICS_TEXTUREDATA_H

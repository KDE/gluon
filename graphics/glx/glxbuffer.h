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

#ifndef GLUONGRAPHICS_GLX_BUFFER_H
#define GLUONGRAPHICS_GLX_BUFFER_H

#include <graphics/buffer.h>

namespace GluonGraphics
{
    namespace GLX
    {
        class GLXBuffer : public GluonGraphics::Buffer
        {
            public:
                GLXBuffer();
                virtual ~GLXBuffer();

                virtual void initialize( BufferType type, UpdateMode mode );
                virtual void destroy();
                virtual void setSize( int size );
                virtual void setData( void* data, int size, int offset = 0 );

                virtual void bind();
                virtual void release();

            private:
                class Private;
                Private* const d;
        };
    }
}

#endif // GLUONGRAPHICS_GLX_BUFFER_H

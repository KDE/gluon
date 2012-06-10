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

#ifndef GLUONGRAPHICS_BUFFER_H
#define GLUONGRAPHICS_BUFFER_H

#include <QVariant>

namespace GluonGraphics
{
    class Buffer
    {
        public:
            enum UpdateMode
            {
                Static,
                Dynamic
            };

            enum BufferType
            {
                Vertex,
                Index
            };

            Buffer() { }
            virtual ~Buffer() { }

            virtual void initialize( BufferType type, UpdateMode mode ) = 0;
            virtual void destroy() = 0;
            virtual void setSize(int size) = 0;
            virtual void setData( const QByteArray& data, int offset = 0 ) = 0;
            virtual void bind() = 0;
            virtual void release() = 0;
    };

}

#endif // GLUONGRAPHICS_BUFFER_H

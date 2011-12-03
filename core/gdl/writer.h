/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GDL_WRITER_H
#define GDL_WRITER_H

#include <QtCore/QScopedPointer>
#include <core/gluonobject.h>

namespace GDL
{
    class Writer
    {
        public:
            Writer();
            virtual ~Writer();

            void write( const GluonCore::GluonObjectList& objects, QIODevice* device );

        private:
            void indent();
            void writeObject( QObject* object );
            void writeProperty( const QString& name, const QVariant& value );

            QString writePropertyValue( const QVariant& value );
            QString writeBoolValue( const QVariant& value );
            QString writeIntValue( const QVariant& value );
            QString writeUIntValue( const QVariant& value );
            QString writeLongLongValue( const QVariant& value );
            QString writeFloatValue( const QVariant& value );
            QString writeStringValue( const QVariant& value );
            QString writeRgbaValue( const QVariant& value );
            QString writeVector2DValue( const QVariant& value );
            QString writeVector3DValue( const QVariant& value );
            QString writeVector4DValue( const QVariant& value );
            QString writeQuaternionValue( const QVariant& value );
            QString writeSize2DValue( const QVariant& value );
            QString writeListValue( const QVariant& value );
            QString writeUrlValue( const QVariant& value );
            QString writeObjectValue( const QVariant& value );

            QIODevice* m_device;
            int m_indentLevel;
    };
}

#endif // GDL_WRITER_H

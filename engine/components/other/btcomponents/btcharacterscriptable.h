/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef BTCHARACTERSCRIPTABLE_H
#define BTCHARACTERSCRIPTABLE_H

#include "engine/gluon_engine_export.h"
#include "smarts/lib/btcharacter.h"

namespace GluonEngine
{
    class BTCOMPONENT_EXPORT btCharacterScriptable : public btCharacter
    {
            Q_OBJECT
            Q_PROPERTY( int time READ time WRITE setTime )
        public:
            btCharacterScriptable( QObject* parent = 0 );
            ~btCharacterScriptable();

            Q_INVOKABLE virtual QVector3D position() const;
            Q_INVOKABLE virtual void setPosition( const QVector3D& newPosition );

            Q_INVOKABLE virtual QQuaternion orientation() const;
            Q_INVOKABLE virtual void setOrientation( const QQuaternion& newOrientation );

            Q_INVOKABLE virtual btPerception* perception();

            Q_INVOKABLE virtual int time();
            Q_INVOKABLE virtual void setTime( int time );

        private:
            int m_time;
    };
}

#endif

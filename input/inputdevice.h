/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#ifndef GLUONINPUT_INPUTDEVICE_H
#define GLUONINPUT_INPUTDEVICE_H

#include <QtCore/QObject>

#include <core/privatepointer.h>

#include "gluoninput_export.h"

namespace GluonInput
{
    class InputParameter;
    class GLUONINPUT_EXPORT InputDevice : public QObject
    {
        Q_OBJECT

        public:
            explicit InputDevice( QObject* parent = 0 );
            virtual ~InputDevice();

            virtual void initialize() = 0;

            virtual QString name() const;

            virtual QList< InputParameter* > parameters() const;

            virtual InputParameter* parameter( const QString& name ) const;
            virtual InputParameter* parameter( int id ) const;

        protected:
            void setName( const QString& name );
            void setParameters( QList< InputParameter* > parameters );

        GLUON_PRIVATE_POINTER;
    };
}

#endif // GLUONINPUT_INPUTDEVICE_H

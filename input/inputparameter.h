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

#ifndef GLUONINPUT_INPUTPARAMETER_H
#define GLUONINPUT_INPUTPARAMETER_H

#include <QtCore/QObject>

#include <core/privatepointer.h>

#include "gluoninput_export.h"

namespace GluonInput
{
    class GLUONINPUT_EXPORT InputParameter : public QObject
    {
        Q_OBJECT
        Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged )
        Q_PROPERTY( ButtonState buttonState READ buttonState WRITE setButtonState NOTIFY buttonStateChanged )
        Q_PROPERTY( int buttonCode READ buttonCode WRITE setButtonCode NOTIFY buttonCodeChanged )
        Q_PROPERTY( bool hasButtonState READ hasButtonState CONSTANT )
        Q_PROPERTY( float axisValue READ axisValue WRITE setAxisValue NOTIFY axisValueChanged )
        Q_PROPERTY( bool hasAxisValue READ hasAxisValue CONSTANT )

        public:
            enum ButtonState
            {
                ButtonUnknown,
                ButtonPressed,
                ButtonReleased,
            };
            Q_ENUMS( ButtonState );

            enum ParameterType
            {
                Button,
                Axis
            };

            explicit InputParameter( ParameterType type, QObject* parent = 0);
            virtual ~InputParameter();

            virtual QString name() const;

            virtual bool hasButtonState() const;

            virtual ButtonState buttonState() const;

            virtual int buttonCode() const;

            virtual bool hasAxisValue() const;

            virtual float axisValue() const;

        public Q_SLOTS:
            virtual void setName( const QString& name );
            virtual void setButtonState( ButtonState state );
            virtual void setButtonCode( int code );
            virtual void setAxisValue( float value );

        Q_SIGNALS:
            void nameChanged();
            void buttonStateChanged();
            void buttonCodeChanged();
            void axisValueChanged();

        private:
            GLUON_PRIVATE_POINTER;
    };
}

#endif // GLUONINPUT_INPUTPARAMETER_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_INPUT_CUSTOMINPUT_H
#define GLUON_INPUT_CUSTOMINPUT_H

#include "gluon_input_export.h"

#include "gluondevices.h"

#include <QtCore/QObject>
#include <QtCore/QSharedDataPointer>

namespace GluonInput
{
    class InputDevice;
    class InputEvent;
    class CustomInputPrivate;

    class GLUON_INPUT_EXPORT CustomInput : public QObject
    {
            Q_OBJECT
        public:
            CustomInput( QObject* parent = 0 );
            virtual ~CustomInput();

            void setButton( const QString& name, InputDevice* input, int keyCode );
            void setButton( const QString& name );
            void remButton( const QString& name );
            void setAbsAxis( const QString& name, InputDevice* input, int axis );
            void setRelAxis( const QString& name, InputDevice* input, int axis );
            void remAbsAxis( const QString& name );
            void remRelAxis( const QString& name );

            QStringList buttonNameList();
            QStringList absAxisNameList();
            QStringList relAxisNameList();

        Q_SIGNALS:
            void buttonPressed( QString name );
            void buttonReleased( QString name );
            void absAxisChanged( QString name, int value );
            void relAxisChanged( QString name, int value );

        private:
            QSharedDataPointer<CustomInputPrivate> d;
    };
}

#endif // GLUON_INPUT_CUSTOMINPUT_H

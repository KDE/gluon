/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Laszlo Papp <lpapp@kde.org>
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

#ifndef TOUCHINPUTCOMPONENT_H
#define TOUCHINPUTCOMPONENT_H

#include <engine/component.h>

namespace GluonInput
{
    class Touch;
}

namespace GluonEngine
{
    class GLUON_COMPONENT_TOUCHINPUT_EXPORT TouchInputComponent : public Component
    {
            Q_OBJECT;
            GLUON_OBJECT( GluonEngine::TouchInputComponent )
            Q_PROPERTY( TouchName touchCode READ touchCode WRITE setTouchCode );
            Q_INTERFACES( GluonEngine::Component )
            Q_ENUMS( KeyName )

        public:
            enum TouchName
            {
                UNKNOWN,
                ONE,
            };

            Q_INVOKABLE TouchInputComponent( QObject* parent = 0 );
            virtual ~TouchInputComponent();
            virtual QString category() const;

            // True on any frame between getActionStarted and
            // getActionStopped, inclusive of those two frames
            Q_INVOKABLE bool isActionHeld();
            // True on the frame when an action was begun (for example the
            // button represented by buttonName was pressed on a controller)
            Q_INVOKABLE bool isActionStarted();
            // True on the frame when an action was stopped (for example a
            // button was released on a controller)
            Q_INVOKABLE bool isActionStopped();

            virtual void initialize();
            virtual void start();
            virtual void update( int elapsedMilliseconds );
            virtual void stop();

            TouchName touchCode() const;
            void setTouchCode( TouchName newTouchCode );

        private:
            bool m_actionHeld;
            bool m_actionStarted;
            bool m_actionStopped;

            TouchName m_touchCode;

            GluonInput::Touch* m_touch;
    };
}

Q_DECLARE_METATYPE( GluonEngine::TouchInputComponent* )

#endif // TOUCHINPUTCOMPONENT_H

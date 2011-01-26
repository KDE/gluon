/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef MOUSEINPUTCOMPONENT_H
#define MOUSEINPUTCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonInput
{
    class Mouse;
}

namespace GluonEngine
{
    class GLUON_COMPONENT_MOUSEINPUT_EXPORT MouseInputComponent : public Component
    {
            Q_OBJECT;
            GLUON_OBJECT( GluonEngine::MouseInputComponent )
            Q_INTERFACES( GluonEngine::Component )
            Q_PROPERTY( MouseButton mouseButton READ mouseButton WRITE setMouseButton )
            Q_PROPERTY( bool mouseTrack READ mouseTrack WRITE setMouseTrack )
            Q_ENUMS( MouseButton )

        public:
            enum MouseButton
            {
                MOUSE_BUTTON_UNKNOWN,
                MOUSE_BUTTON_LEFT,
                MOUSE_BUTTON_RIGHT,
                MOUSE_BUTTON_MIDDLE,
                MOUSE_BUTTON_FOUR,
                MOUSE_BUTTON_FIVE,
                MOUSE_BUTTON_SIX,
                MOUSE_BUTTON_SEVEN,
                MOUSE_BUTTON_EIGHT,
            };

            Q_INVOKABLE MouseInputComponent( QObject* parent = 0 );
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

            MouseButton mouseButton() const;
            void setMouseButton( MouseButton button );

            bool mouseTrack() const;
            void setMouseTrack( bool enable );

            Q_INVOKABLE virtual int xAxis();
            Q_INVOKABLE virtual int yAxis();
            Q_INVOKABLE virtual int zAxis();

            Q_INVOKABLE virtual int relativeXAxis();
            Q_INVOKABLE virtual int relativeYAxis();
            Q_INVOKABLE virtual int relativeZAxis();

        private:
            class MouseInputComponentPrivate;
            MouseInputComponentPrivate* const d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::MouseInputComponent )
Q_DECLARE_METATYPE( GluonEngine::MouseInputComponent* )

#endif // MOUSEINPUTCOMPONENT_H

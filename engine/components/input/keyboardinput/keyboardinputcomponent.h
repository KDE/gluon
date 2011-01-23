/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef KEYBOARDINPUTCOMPONENT_H
#define KEYBOARDINPUTCOMPONENT_H

#include "component.h"

#include "gluonbuttons.h"

namespace GluonInput
{
    class Keyboard;
}

namespace GluonEngine
{
    class KeyboardInputComponent : public Component
    {
            Q_OBJECT;
            GLUON_OBJECT( GluonEngine::KeyboardInputComponent )
            Q_PROPERTY( Qt::Key keyCode READ keyCode WRITE setKeyCode );
            Q_INTERFACES( GluonEngine::Component )

        public:

            Q_INVOKABLE KeyboardInputComponent( QObject* parent = 0 );
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

            Qt::Key keyCode() const;
            void setKeyCode( Qt::Key newKeyCode );

        private:
            bool m_actionHeld;
            bool m_actionStarted;
            bool m_actionStopped;

            Qt::Key m_keyCode;

            GluonInput::Keyboard* m_keyboard;
    };
}

Q_DECLARE_METATYPE( GluonEngine::KeyboardInputComponent )
Q_DECLARE_METATYPE( GluonEngine::KeyboardInputComponent* )

#endif // KEYBOARDINPUTCOMPONENT_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_ENGINE_SOUNDLISTENERCOMPONENT_H
#define GLUON_ENGINE_SOUNDLISTENERCOMPONENT_H

#include <engine/component.h>

namespace GluonEngine
{

    class GLUON_COMPONENT_SOUNDLISTENER_EXPORT SoundListenerComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::SoundListenerComponent )
            Q_PROPERTY( bool active READ isActive WRITE setActive )
            Q_PROPERTY( bool effectsEnabled READ effectsEnabled WRITE setEffectsEnabled )

            Q_INTERFACES( GluonEngine::Component )

        public:
            Q_INVOKABLE SoundListenerComponent( QObject* parent = 0 );
            SoundListenerComponent( const SoundListenerComponent& other );
            virtual QString category() const;

            virtual void start();
            virtual void draw( int timeLapse = 0 );

            void setActive( bool active );
            bool isActive()
            {
                return m_activeInstance == this;
            }

            void setEffectsEnabled( bool enable );
            bool effectsEnabled()
            {
                return m_effectsEnabled;
            }

            static SoundListenerComponent* activeInstance();

        private:
            bool m_effectsEnabled;

            static SoundListenerComponent* m_activeInstance;
    };

}

Q_DECLARE_METATYPE( GluonEngine::SoundListenerComponent* )

#endif // GLUON_ENGINE_SOUNDLISTENERCOMPONENT_H

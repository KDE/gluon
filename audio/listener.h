/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2014 Felix Rohrbach <kde@fxrh.de>
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

#ifndef GLUON_AUDIO_LISTENER_H
#define GLUON_AUDIO_LISTENER_H

#include "gluon_audio_export.h"

#include <core/singleton.h>

#include <QtCore/QObject>

#include <Eigen/Core>

namespace GluonAudio
{
    class Channel;
    class Source;
    
    class GLUON_AUDIO_EXPORT Listener : public GluonCore::Singleton<Listener>
    {
            Q_OBJECT
            GLUON_SINGLETON( Listener )
        public:
            float masterVolume() const;
            void setMasterVolume( float vol );
            
            QList<Channel*> channels() const;
            void addChannel( Channel* channel );
            
            QList<Source*> sources() const;
            void addSource( Source* source );

            /**
            * Position of the listener in 3D
            * @see Sound::setPosition
            */
            Eigen::Vector3f listenerPosition();
            void setListenerPosition( const Eigen::Vector3f& position );

        private:
            ~Listener();

            class Private;
            Private* const d;
    };
}

#endif // GLUON_AUDIO_LISTENER_H

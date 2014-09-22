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
    
    /**
     * The Listener is at the position of the player in the game and "hears" the different sources.
     * It can also be used to set the master volume.
     */
    class GLUON_AUDIO_EXPORT Listener : public GluonCore::Singleton<Listener>
    {
            Q_OBJECT
            GLUON_SINGLETON( Listener )
        public:
            /**
             * Get the master volume level. By default, this is 1.0f.
             */
            float masterVolume() const;
            
            /**
             * Set the master volume level. @p vol has to be non-negative.
             */
            void setMasterVolume( float vol );
            
            /**
             * Return a list of channels added to the Listener.
             */
            QList<Channel*> channels() const;
            
            /**
             * Add a channel to this listener.
             */
            void addChannel( Channel* channel );
            
            /**
             * Get a list of sources added to the Listener.
             */
            QList<Source*> sources() const;
            
            /**
             * Add a source to the Listener. Every source you wish to hear has to be added to the Listener, 
             * directly or indirectly via channels.
             */
            void addSource( Source* source );

            /**
            * Get the position of the listener. (0.f,0.f,0.f) as default.
            * @see Source::position()
            */
            Eigen::Vector3f listenerPosition();
            
            /**
             * Set the position of the listener.
             * @see Source::setPosition()
             */
            void setListenerPosition( const Eigen::Vector3f& position );

        private:
            ~Listener();

            class Private;
            Private* const d;
    };
}

#endif // GLUON_AUDIO_LISTENER_H

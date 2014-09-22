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

#ifndef GLUON_AUDIO_CHANNEL_H
#define GLUON_AUDIO_CHANNEL_H

#include <QtCore/QList>

#include "source.h"
#include "gluon_audio_export.h"

namespace GluonAudio
{
    /**
     * A channel groups together a number of sources or other channels, setting a volume for all of them. The
     * volume of a source is calculated by multiplicating the source volume with all parent channel volumes and
     * the master volume.
     */
    class GLUON_AUDIO_EXPORT Channel: public QObject
    {
            Q_OBJECT
        public:
            Channel( QObject* parent=0 );
            virtual ~Channel();
            
            bool isValid() const;
            
            /**
             * Set the volume of this channel. It has to be non-negative.
             */
            void setChannelVolume( float volume );
            
            /**
             * returns the channel volume. The default is 1.0f.
             */
            float channelVolume() const;
            
            /**
             * Add a subchannel to this channel.
             */
            void addSubchannel( Channel* subchannel );
            
            /**
             * Get the list of subchannels.
             */
            QList<Channel*> subchannels() const;
            
            /**
             * Add a source to this channel.
             */
            void addSource( Source* source );
            
            /**
             * Get a list of sources added to this channel.
             */
            QList<Source*> sources() const;
            
            /**
             * Called by the parent channel to calculate the effective volume for every source.
             */
            void setParentChannelVolume( float volume );
            
        private:
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_CHANNEL_H
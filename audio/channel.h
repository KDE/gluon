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

namespace GluonAudio
{
    class Channel: public QObject
    {
            Q_OBJECT
        public:
            Channel( QObject* parent=0 );
            virtual ~Channel();
            
            bool isValid() const;
            
            void setChannelVolume( float volume );
            float channelVolume() const;
            
            void addSubchannel( Channel* subchannel );
            QList<Channel*> subchannels() const;
            void addSource( Source* source );
            QList<Source*> sources() const;
            
            void setParentChannelVolume( float volume );
            
        private:
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_CHANNEL_H
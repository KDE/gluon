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

#ifndef GLUON_AUDIO_SOURCE_H
#define GLUON_AUDIO_SOURCE_H

#include <QtCore/QObject>

#include <Eigen/Core>

#include "gluon_audio_export.h"

namespace GluonAudio
{

    class GLUON_AUDIO_EXPORT Source: public QObject
    {
            Q_OBJECT
        public:
            enum PlayingState { Started, Stopped, Paused };
            
            Source(QObject* parent=0);
            virtual ~Source();
            
            void queueBuffer(unsigned int bufferName);
            int removeOldBuffers();
            
            void fileNearlyFinished();
            
            bool isValid() const;
            
            bool isAmbient() const;
            void setAmbient( bool isAmbient );
            
            void setPosition( Eigen::Vector3f pos );
            Eigen::Vector3f position() const;
            
            float volume() const;
            float realVolume() const;
            void setVolume( float volume );
            
            void setParentChannelVolume( float volume );
            
        public Q_SLOTS:
            void play();
            void pause();
            void stop();
            
        Q_SIGNALS:
            void queueNext();
            
        private:
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_SOURCE_H
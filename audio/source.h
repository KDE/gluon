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

#include "buffer.h"

#include "gluon_audio_export.h"

namespace GluonAudio
{
    class AbstractPlaylist;
    
    /**
     * Source is an audio source at some place in the game. If the listener is near 
     * enough (or it's ambient sound), you will hear its sounds. It's a wrapper around
     * the OpenAL source object.
     */
    class GLUON_AUDIO_EXPORT Source: public QObject
    {
            Q_OBJECT
        public:
            Source(QObject* parent=0);
            virtual ~Source();
            
            /**
             * Add more or the initial buffers to the source. This should be done via an
             * AudioFile object.
             */
            void queueBuffer(Buffer buffer);
            
            /**
             * Returns the current number of buffers the source has.
             */
            int getNumberOfBuffers();
            
            /**
             * Remove all buffers that are processed and not needed any longer.
             * @returns the number of buffers removed
             */
            int removeOldBuffers();
            
            /**
             * Tell the source a file was added. This should be called by AudioFile.
             */
            void audioFileAdded();
            
            /**
             * Remove leftovers from a file not finished playing.
             */
            void clear();
            
            bool isValid() const;
            
            /**
             * Checks whether the Source is global.
             * Global sources can be heard everywhere.
             * Note: Stereo output is always global.
             */
            bool isGlobal() const;
            
            /**
             * Set whether this source is global or not.
             * @see isGlobal()
             */
            void setGlobal( bool isAmbient );
            
            /**
             * Get the position of the Source. This (and the position of the listener) decides how loud and from
             * which direction you hear the sound.
             */
            Eigen::Vector3f position() const;
            
            /**
             * Set the position of the Source. You are not able to do this if the source is ambient.
             * @see position()
             */
            void setPosition( Eigen::Vector3f pos );
            
            /**
             * Get the volume set for this source.
             */
            float volume() const;
            
            /**
             * Get the real volume of this source, based on its volume and the volume of the channel it belongs to.
             */
            float realVolume() const;
            
            /**
             * Set the volume for this source. Volume must be positive or 0.
             */
            void setVolume( float volume );
            
            /**
             * Called by the parent channel.
             */
            void setParentChannelVolume( float volume );
            
            /**
             * The position (in seconds) in the currently loaded buffers
             */
            float positionInBuffers();
            
            /**
             * The remaining time in the buffer in seconds
             */
            float remaingTime();
            
            /**
             * Get the maximal buffer size for each file
             */
            float getMaxBufferSize();
            
            /**
             * The current playlist
             */
            AbstractPlaylist* playlist() const;
            
            /**
             * Set the current playlist
             */
            void setPlaylist( AbstractPlaylist* playlist );
            
            /**
             * Pause playback
             */
            void pause();
            
            /**
             * Continue playback after pause
             */
            void continuePlaying();
            
            /**
             * Stop playing
             */
            void stop();
            
            /**
             * Regular called function to do stuff (like checking if the buffer ran out)
             */
            void update();
            
            float pitch() const;
            void setPitch( float pitch );
            
            float radius() const;
            void setRadius( float radius );
            
        signals:
            void endOfBuffer(Source* s);
            
            
        private:
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_SOURCE_H
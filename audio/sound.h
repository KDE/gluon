/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2009-2011 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_AUDIO_SOUND_H
#define GLUON_AUDIO_SOUND_H

#include "gluon_audio_export.h"

#include <QtCore/QObject>

#include <Eigen/Core>

namespace GluonAudio
{
    class GLUON_AUDIO_EXPORT Sound : public QObject
    {
            Q_OBJECT

        public:
            enum Status
            {
                INITIAL,
                PLAYING,
                PAUSED,
                STOPPED,
            };

            /**
            * Constructs an empty, invalid Sound object
            * @see isValid, load
            */
            explicit Sound( QObject* parent = 0 );

            /**
            * @param fileName the path of the file to play
            */
            explicit Sound( const QString& fileName, QObject* parent = 0 );

            /**
            * Destructor
            */
            virtual ~Sound();

            /**
            * Load a new sound file
            */
            bool load( const QString& fileName );

            /**
            * An object is invalid when no file is loaded or the last file
            * was incorrectly loaded. The only function that should be used
            * on such an object is load.
            * @see load
            */
            bool isValid() const;

            /**
            * Stop the sound, mark the object as invalid and delete the
            * underlying OpenAL source. Useful to avoid going over the
            * limit of concurrent sources.
            */
            void clear();

            /**
            * @return the time since the sound started playing
            * If there is no source loaded, it returns -1.
            */
            float timeOffset() const;

            /**
             * Returns true if it is currently playing; otherwise returns false
             * if it is currently stopped or paused
             */
            bool isPlaying() const;

            /**
             * Returns true if it is currently paused; otherwise returns false
             * if it is currently playing or stopped
             */
            bool isPaused() const;

            /**
             * Returns true if it is currently stopped; otherwise returns false
             * if it is currently playing or paused
             */
            bool isStopped() const;

            /**
            * Returns true if the sound was set to loop, false otherwise.
            * By default, files are set not to loop.
            */
            bool isLooping() const;

            /**
            * @todo this function isn't defined!
            * @return the last error reported
            */
            QString lastError() const;

            /**
            * @return the coordinates of the sound postion
            * relative to the listener
            * @see setPosition, x, y, z
            */
            Eigen::Vector3f position() const;

            /**
            * @return the x coordinate of the sound position
            * relative to the listener
            * @see setPosition, y, z
            */
            float x() const;

            /**
            * @return the y coordinate of the sound position
            * relative to the listener
            * @see setPosition, x, z
            */
            float y() const;

            /**
            * @return the z coordinate of the sound position
            * relative to the listener
            * @see setPosition, x, y
            */
            float z() const;

            /**
            * @return the volume currently applied.
            * If there is no source loaded, it returns -1.
            * @see setVolume
            */
            float volume() const;

            /**
            * @return the pitch currently applied
            * @see setPitch
            */
            float pitch() const;

            /**
             * @return the file radius currently applied
             * @see setRadius
             */
            float radius() const;

            /**
            * @return the file sound duration in seconds
            */
            double duration() const;
            //ALfloat duration() const;

        public Q_SLOTS:
            /**
            * Plays the sound file from the beginning or from the moment
            * pause() was called
            * @see pause, stop, rewind
            */
            void play();

            /**
            * Pauses the sound currently played
            * @see play, stop, rewind
            */
            void pause();

            /**
            * Stops the sound currently played
            * @see play, pause, rewind
            */
            void stop();

            /**
            * If the sound was paused, this will rewind it so that next time
            * play() is called, it will play from the start
            */
            void rewind();

            /**
            * Makes the sound play in a loop when play() is called
            * @p enabled play in a loop if set to true
            *
            * If there is no source loaded, it does not set the looping.
            * @see play
            */
            void setLoop( bool enabled = true );

            /**
            * Set the position of the sound relative to the listener.
            * This is used to create 3D sounds using effects to alter
            * the perception of the sound origin.
            * The three scalars of the vector correspond to x, y and z in
            * the coordinate system.
            *
            * The OpenAL documentation defines the underlying variable as:
            * "Specify the current location in three dimensional space.
            * OpenAL, like OpenGL, uses a right handed coordinate system,
            * where in a frontal default view x (thumb) points right,
            * y points up (index finger), and z points towards the
            * viewer/camera (middle finger).
            * To switch from a left handed coordinate system, flip the
            * sign on the Z coordinate.
            * Listener position is always in the world coordinate system."
            *
            * If there is no source loaded, it does not set the position.
            */
            void setPosition( Eigen::Vector3f position );

            /**
            * @overload setPosition()
            * Set the position of the sound relative to the listener
            * using the coordinates (@p x, @p y, @p z).
            *
            * If there is no source loaded, it does not set the position.
            */
            void setPosition( float x = 0.0, float y = 0.0, float z = 0.0 );

            /**
            * Change the volume (volume amplification) applied
            *
            * The OpenAL documentation defines the underlying variable as:
            * "A value of 1.0 means un-attenuated/unchanged.
            * Each division by 2 equals an attenuation of -6dB.
            * Each multiplicaton with 2 equals an amplification of +6dB.
            * A value of 0.0 is meaningless with respect to a logarithmic
            * scale; it is interpreted as zero volume - the channel
            * is effectively disabled."
            * The range that can be set is 0.0f - 1.0f
            *
            * If there is no source loaded, it does not set the volume.
            * @see volume
            */
            void setVolume( float volume = 1.0f );

            /**
            * Specify the pitch to be applied, either at source,
            * or on mixer results, at listener.
            * @param pitch a value between 0.5 and 2.0
            *
            * If there is no source loaded, it does not set the pitch.
            */
            void setPitch( float pitch = 1.0f );

            /**
             * Specify the distance from which the sound can no longer be heard
             * @param radius A length
             *
             * If there is no source loaded, it does not set the radius.
             */
            void setRadius( float radius = 10000.0f );

            /**
            * Set the velocity of the sound relative to the listener
            * using the coordinates (@p x, @p y, @p z).
            *
            * If there is no source loaded, it does not set the velocity.
            */
            void setVelocity( float vx, float vy, float vz );

            /**
            * Set the direction of the sound relative to the listener
            * using the coordinates (@p x, @p y, @p z).
            *
            * If there is no source loaded, it does not set the direction.
            */
            void setDirection( float dx, float dy, float dz );

            /**
            * Specify the current time offset.
            * @param time must be inferior than duration.
            * @see duration()
            */
            void setTimeOffset( float time );

        Q_SIGNALS:
            void played();
            void paused();

            /**
             * Emitted when a sound finishs. Not emitted when stop
             * is called.
             */
            void soundFinished();

        private:
            Q_DISABLE_COPY( Sound )
            static void callbackStopped( void* object, uint source );
            void cbStop();

            class SoundPrivate;
            SoundPrivate* const d;
            Q_PRIVATE_SLOT( d, void _k_deleteSource() );
    };
}

#endif // GLUON_AUDIO_SOUND_H

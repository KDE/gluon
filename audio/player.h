/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Michał Koźmiński <michal.kozminski@gmail.com>
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

#ifndef GLUON_AUDIO_PLAYER_H
#define GLUON_AUDIO_PLAYER_H

#include "gluon_audio_export.h"

#include "sound.h"

#include <QtCore/QStringList>

namespace GluonAudio
{
    class GLUON_AUDIO_EXPORT Player : public QObject
    {
            Q_OBJECT

        public:
            /**
             * Constructs a new and empty Player instance with the specified
             * parent.
             */
            Player( QObject* parent = 0 );

            /**
             * Constructs an playback with the files passed
             *
             * @param files The files with that the playback is constructed
             */
            explicit Player( QStringList files, QObject* parent = 0 );

            /**
             * On destruction the playback is stopped
             */
            virtual ~Player();

            /**
             * Appends the given sound from file to the end of the playback
             *
             * @see insert(), removeLast(), removeAt()
             */
            void append( QString file );

            /**
             * Inserts the given sound at the given index position in the
             * playback
             *
             * @see append(), removeLast(), removeAt()
             */
            void insert( int index, QString file );

            /**
             * Removes the last sound in the list. Calling this function is
             * equivalent to calling removeAt(size - 1). The list must not be
             * empty. If the list can be empty, call isEmpty() before calling
             * this function.
             *
             * @see removeAt(), insert(), append()
             */
            void removeLast();

            /**
             * Removes the sound at index position i. i must be a valid index
             * position in the list (i.e., 0 <= i < size).
             *
             * @see removeLast(), append(), insert()
             */
            void removeAt( int index );

            /**
             * Returns true if it is currently playing; otherwise returns false
             * if it is currently stopped or paused
             */
            bool isPlaying() const;

            /**
             * This is the current volume of the given sound.
             *
             * @see setVolume(), Sound::volume()
             */
            ALfloat volume() const;

            /**
             * Sets the volume of the output as voltage factor.
             * @see Sound::setVolume
             *
             * @set volume(), Sound::setVolume()
             */
            void setVolume( ALfloat volume = 1.0f );

            /**
             * Returns true if the given list of sounds was set to loop, false otherwise.
             * By default, files are set not to loop.
             *
             * @see setLoop(), Sound::isLooping()
             */
            bool isLooping() const;

            /**
             * Makes the given list of sounds play in a loop when play() is called
             * @loop enables play list in a loop if set to true
             *
             * @see isLooping(), Sound::setLoop()
             */
            void setLoop( bool loop );

            /**
             * Returns the pitch currently applied of the given sound
             *
             * @see setPitch(), Sound::pitch()
             */
            ALfloat pitch() const;

            /**
             * Specify the pitch to be applied for the given sound
             * @param pitch a value between 0.5 and 2.0
             *
             * @see pitch(), Sound::setPitch()
             */
            void setPitch( ALfloat pitch );

            QStringList files();

        public Q_SLOTS:

            /**
             * Plays the media from the sound.
             *
             * @see playNext(), playAt()
             */
            void play();

            /**
             * Plays the media from the next sound.
             *
             * @see playAt(), play()
             */
            void playNext();

            /**
             * Plays the media from the sound with the given index.
             *
             * @see play(), playNext()
             */
            void playAt( int index );

            /**
             * Pauses the playback.
             */
            void pause();

            /**
             * Seeks to the requested time.
             *
             * @param ms The ms parameter is the time in milliseconds from the
             * start of the media.
             */
            void seek( qint64 ms );

            /**
             * Stops the playback.
             */
            void stop();

        Q_SIGNALS:
            /**
             * This signal is emitted when the playback finished.
             */
            void finished();

        private:
            class PlayerPrivate;
            PlayerPrivate* const d;
    };
}

#endif // GLUON_AUDIO_PLAYER_H

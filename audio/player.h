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
            explicit Player( QObject* parent = 0 );
            explicit Player( QStringList files, QObject* parent = 0 );
            virtual ~Player();

            void append( QString file );
            void insert( int index, QString buffer );

            void removeLast();
            void removeAt( int index );

            bool isPlaying() const;

            ALfloat volume() const;
            void setVolume(ALfloat volume = 1.0f);

            bool isLooping() const;
            void setLoop(bool loop);

            ALfloat pitch() const;
            void setPitch(ALfloat pitch);

        public Q_SLOTS:
            void play();
            void playNext();
            void playAt(int index);
            void pause();
            void seek();
            void stop();

        Q_SIGNALS:
            void finished();

        private:
            class PlayerPrivate;
            PlayerPrivate* const d;

    };
}

#endif // GLUON_AUDIO_PLAYER_H

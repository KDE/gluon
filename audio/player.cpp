/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Michał Koźmiński <michal.kozminski@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "player.h"

#include <QtCore/QVector>

using namespace GluonAudio;

class Player::PlayerPrivate
{
    public:
        PlayerPrivate()
            : sound( new Sound() )
            , currentIndex( 0 )
            , playerLoop( false )

        {
        }

        ~PlayerPrivate()
        {
        }

        QStringList files;
        Sound* sound;
        int currentIndex;
        ALfloat soundVolume;
        ALfloat soundPitch;
        bool playerLoop;
};

Player::Player(QObject* parent)
    : QObject(parent)
    , d( new PlayerPrivate )
{
    connect(d->sound, SIGNAL( paused() ), SLOT( playNext() ) );
    connect(d->sound, SIGNAL( stopped() ), SLOT( playNext() ) );
}

void Player::removeAt(int index)
{
    if( d->files.count()-1 >= index )
	    d->files.removeAt( index );
}

void Player::append(QString file)
{
    d->files.append( file );
}

void Player::insert(int index, QString file)
{
    if( d->files.count()-1 > index )
        d->files.append(file);
    else
        d->files.replace( index, file );
}

void Player::removeLast()
{
    d->files.removeAt( d->files.size()-1 );
}

void Player::play()
{
    d->sound->load( d->files.at( d->currentIndex ) );
    d->sound->setVolume(d->soundVolume);
    d->sound->play();
}

void Player::playAt(int index)
{
    d->sound->load(d->files.at(index));
    d->sound->play();
}

void Player::pause()
{
    d->sound->pause();
}

void Player::seek()
{
}

void Player::stop()
{
    d->sound->stop();
}

bool Player::isPlaying() const
{
    return d->sound->isPlaying();
}

ALfloat Player::pitch() const
{
    return d->soundPitch;
}

void Player::setPitch(ALfloat pitch)
{
    d->soundPitch = pitch;
    d->sound->setPitch(pitch);
}

void Player::setVolume(ALfloat volume)
{
    d->soundVolume = volume;
}

ALfloat Player::volume() const
{
    return d->soundVolume;
}

void Player::setLoop(bool loop)
{
    d->playerLoop = loop;
}

bool Player::isLooping() const
{
    return d->playerLoop;
}

void Player::playNext()
{
    if( d->files.count()-1 == d->currentIndex )
    {
        if( d->playerLoop )
        {
            d->currentIndex = 0;
        }
        else
        {
            emit finished();
            return;
        }
    }
    else
    {
        ++d->currentIndex;

    }

    play();
}

#include "player.moc"

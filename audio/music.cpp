/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
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
#include "music.h"

#include <QtCore/QDebug>

using namespace GluonAudio;

static const int BUFFER_SIZE = 4096 * 4;

Music::Music( QString fileName )
{
    setFileName( fileName );
}

void Music::open( std::string path )
{
    int result;

    if( !( oggFile = fopen( path.c_str(), "rb" ) ) )
        qDebug() << "Could not open Ogg file.";

    if(( result = ov_open( oggFile, &oggStream, 0, 0 ) ) < 0 )
    {
        fclose( oggFile );
        qDebug() << "Could not open Ogg stream. ";
    }

    vorbisInfo = ov_info( &oggStream, -1 );
    vorbisComment = ov_comment( &oggStream, -1 );

    if( vorbisInfo->channels == 1 )
    {
        format = AL_FORMAT_MONO16;
    }
    else
    {
        format = AL_FORMAT_STEREO16;
    }

    alGenBuffers( 2, buffers );
    check();
    alGenSources( 1, &source );
    check();

    alSource3f( source, AL_POSITION, 0.0, 0.0, 0.0 );
    alSource3f( source, AL_VELOCITY, 0.0, 0.0, 0.0 );
    alSource3f( source, AL_DIRECTION, 0.0, 0.0, 0.0 );
    alSourcef( source, AL_ROLLOFF_FACTOR, 0.0 );
    alSourcei( source, AL_SOURCE_RELATIVE, AL_TRUE );
}

void Music::release()
{
    alSourceStop( source );
    empty();
    alDeleteSources( 1, &source );
    check();
    alDeleteBuffers( 1, buffers );
    check();

    ov_clear( &oggStream );
}

void Music::display()
{
    qDebug()
            << "version         " << vorbisInfo->version         << "\n"
            << "channels        " << vorbisInfo->channels        << "\n"
            << "rate (hz)       " << vorbisInfo->rate            << "\n"
            << "bitrate upper   " << vorbisInfo->bitrate_upper   << "\n"
            << "bitrate nominal " << vorbisInfo->bitrate_nominal << "\n"
            << "bitrate lower   " << vorbisInfo->bitrate_lower   << "\n"
            << "bitrate window  " << vorbisInfo->bitrate_window  << "\n"
            << "\n"
            << "vendor " << vorbisComment->vendor << "\n";

    for( int i = 0; i < vorbisComment->comments; ++i )
    {
        qDebug() << "   " << vorbisComment->user_comments[i] << "\n";
    }
}

bool Music::playback()
{
    if( isPlaying() )
    {
        return true;
    }

    if( !stream( buffers[0] ) )
    {
        return false;
    }

    if( !stream( buffers[1] ) )
    {
        return false;
    }

    alSourceQueueBuffers( source, 2, buffers );
    alSourcePlay( source );

    return true;
}

bool Music::isPlaying() const
{
    ALenum state;

    alGetSourcei( source, AL_SOURCE_STATE, &state );

    return ( state == AL_PLAYING );
}

bool Music::update()
{
    int processed;
    bool active = true;

    alGetSourcei( source, AL_BUFFERS_PROCESSED, &processed );

    while( --processed )
    {
        ALuint buffer;

        alSourceUnqueueBuffers( source, 1, &buffer );
        check();

        active = stream( buffer );

        alSourceQueueBuffers( source, 1, &buffer );
        check();
    }

    return active;
}

bool Music::stream( ALuint buffer )
{
    char pcm[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while( size < BUFFER_SIZE )
    {
        result = ov_read( &oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section );

        if( result > 0 )
        {
            size += result;
        }
        else
        {
            if( result < 0 )
            {
                qDebug() << "errorString(result)";
            }
            else
            {
                break;
            }
        }
    }

    if( size == 0 )
    {
        return false;
    }

    alBufferData( buffer, format, pcm, size, vorbisInfo->rate );
    check();

    return true;
}

void Music::empty()
{
    int queued;

    alGetSourcei( source, AL_BUFFERS_QUEUED, &queued );

    while( --queued )
    {
        ALuint buffer;

        alSourceUnqueueBuffers( source, 1, &buffer );
        check();
    }
}

void Music::check()
{
    int error = alGetError();

    if( error != AL_NO_ERROR )
    {
        qDebug() << "OpenAL error was raised.";
    }
}

std::string Music::errorString( int code )
{
    switch( code )
    {
        case OV_EREAD:
            return std::string( "Read from media." );
        case OV_ENOTVORBIS:
            return std::string( "Not Vorbis data." );
        case OV_EVERSION:
            return std::string( "Vorbis version mismatch." );
        case OV_EBADHEADER:
            return std::string( "Invalid Vorbis header." );
        case OV_EFAULT:
            return std::string( "Internal logic fault (bug or heap/stack corruption." );
        default:
            return std::string( "Unknown Ogg error." );
    }
}

void Music::run()
{
    open( m_fileName.toUtf8().data() );
    display();
    if( !playback() )
    {
        qDebug() << "Ogg refused to play.";
    }

    while( update() )
    {
        if( !isPlaying() )
        {
            if( !playback() )
            {
                qDebug() << "Ogg abruptly stopped.";
            }
            else
            {
                qDebug() << "Ogg stream was interrupted.\n";
            }
        }
    }
    release();
}

#include "music.moc"

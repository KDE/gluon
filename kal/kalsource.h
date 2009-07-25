/*
* This file is part of the KALEngine project.
* Copyright (C) 2007 Laurent Gomila <laurent.gom@gmail.com>
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#ifndef KALSOURCE_H
#define KALSOURCE_H

#include <alut.h>
#include <QtCore/QFile>
#include <QtGui/QProgressBar>
#include <QtCore/QThread>

#include "kalengine_export.h"
#include "kalbuffer.h"

/**
* @class KALSource kalsource.h <KALSource>
* KALSource lets you play an audio file in a separate thread
*/
class KALENGINE_EXPORT KALSource : public QObject
{
    Q_OBJECT
    
public:
    /**
    * This is the default constructor
    * @param soundFile the path of the file to play
    */
    KALSource(const QString &soundFile,QObject * parent=0);
    /**
    * This is the default constructor
    * @param KALBuffer the buffer
    */
    KALSource(KALBuffer *buffer,QObject * parent=0);
    /**
    * This is the default constructor
    * @param ALuint the buffer
    */
    KALSource(ALuint buffer,QObject * parent=0);
    
    
    //
    void setBuffer(const QString& soundFile) { m_buffer=new KALBuffer(soundFile);}
    void setBuffer(KALBuffer * buffer){m_buffer = buffer;}
    void setBuffer(ALuint buffer){m_buffer = new KALBuffer(buffer);}
    
    
    /**
    * Destructor
    */
    ~KALSource();
    
    /**
    * @return the time since the sound started playing
    */
    ALfloat elapsedTime();
    
    /**
    * @return the sound status
    */
    ALint status();
    
    /**
    * @todo this function isn't defined!
    * @return the last error reported
    */
    QString lastError();
    
    /**
    * @return the x position of the listener
    * @see setPosition, y, z
    */
    ALfloat x();
    
    /**
    * @return the y position of the listener
    * @see setPosition, x, z
    */
    ALfloat y();
    
    /**
    * @return the z position of the listener
    * @see setPosition, x, y
    */
    ALfloat z();
    
    /**
    * @return the gain currently applied
    * @see setGain
    */
    ALfloat gain();
    
    /**
    * @return the pitch currently applied
    * @see setPitch
    */
    ALfloat pitch();
    
    
protected:
    void init();
    
    
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
    * @see play
    */
    void loop(bool enabled = true);
    
    
    
    /**
    * Sets the position of the listener, this is used to create
    * 3D sounds using effects to artificially change sound origin
    * The openAL documentation defines the underlying variable as:
    * Specify the current location in three dimensional space.
    * OpenAL, like OpenGL, uses a right handed coordinate system,
    * where in a frontal default view @p x (thumb) points right,
    * @p y points up (index finger), and @p z points towards the
    * viewer/camera (middle finger).
    * To switch from a left handed coordinate system, flip the
    * sign on the Z coordinate.
    * Listener position is always in the world coordinate system.
    */
    void setPosition(ALfloat x = 0.0, ALfloat y = 0.0, ALfloat z = 0.0);
    
    /**
    * Change the gain (volume amplification) applied
    * The openAL documentation defines the underlying variable as:
    * A value of 1.0 means un-attenuated/unchanged.
    * Each division by 2 equals an attenuation of -6dB.
    * Each multiplicaton with 2 equals an amplification of +6dB.
    * A value of 0.0 is meaningless with respect to a logarithmic
    *  scale; it is interpreted as zero volume - the channel
    *  is effectively disabled.
    * @see gain
    */
    void setGain(ALfloat volume = 1.0f);
    
    /**
    * Specify the pitch to be applied, either at source,
    * or on mixer results, at listener.
    * @param pitch a value between 0.5 and 2.0
    */
    void setPitch(ALfloat pitch = 1.0f);
    
    
    void setMinGain(ALfloat min = 0.0f);
    void setMaxGain(ALfloat max = 10.0f);
    void setVelocity(ALfloat vx, ALfloat vy, ALfloat vz);
    void setDirection(ALfloat dx, ALfloat dy, ALfloat dz);
    
    void setupSource();
    void updateSource();
private:
    
    
    bool m_toPlay;
    
    
    
    KALBuffer *m_buffer;
    ALuint m_source;
    ALfloat m_x;
    ALfloat m_y;
    ALfloat m_z;
    ALfloat m_gain;
    ALfloat m_pitch;
    
    
    
    
    
    
};

#endif // KALSOURCE_H

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

#ifndef GLUON_AUDIO_ABSTRACTFILE_H
#define GLUON_AUDIO_ABSTRACTFILE_H

#include <QtCore/QObject>
#include "gluon_audio_export.h"

namespace GluonAudio
{
    class Source;
    class Buffer;
    
    /**
     * AbstractFile represents an audio file on your disk, used to stream it to an audio source in your game.
     * Different file classes (like MusicFile and EffectFile) behave different in the way they manage the streaming.
     */
    class GLUON_AUDIO_EXPORT AbstractFile : public QObject
    {
            Q_OBJECT
        public:
            /**
             * Create an AbstractFile.
             * @p file The path to the audio file
             * @p parent The parent object
             */
            AbstractFile( QString file, QObject* parent=0 );
            virtual ~AbstractFile();
            
            virtual bool isValid();
            
            /**
             * Start streaming this file to the source
             */
            virtual void feedSource( Source* source )=0;
            
            /**
             * Stop streaming this file to the source
             */
            virtual void stopFeedingSource( Source* source )=0;
            
            /**
             * Regularly called to do things like moving buffered data from the decoder
             * to the source.
             */
            virtual void update()=0;
            
        protected:
            /**
             * The path of the file this instance represents
             */
            QString file();
            
            /**
             * Generate an OpenAL-internal buffer with the given data.
             */
            bool generateBuffer( Buffer* buffer, bool isStereo );
            
        private:
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_ABSTRACTFILE_H
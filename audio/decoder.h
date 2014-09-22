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
#ifndef GLUON_AUDIO_DECODER_H
#define GLUON_AUDIO_DECODER_H

#include "gluon_audio_export.h"

#include "buffer.h"

namespace GluonAudio
{
    /**
     * Reads and decodes an audio file into small buffers. Each decoder subclass has a DecoderPlugin class which creates instances of it.
     */
    class GLUON_AUDIO_EXPORT Decoder
    {
        public:
            virtual ~Decoder() {};
            
            /**
             * Start decoding the file. 
             */
            virtual void startDecoding()=0;
            
            /**
             * Stop decoding the file.
             */
            virtual void stopDecoding()=0;
            
            /**
             * Set the preferred size of one buffer
             */
            virtual void setBufferSize( int bytes )=0;
            
            /**
             * Returns the number of new buffers currently available
             */
            virtual bool buffersAvailable()=0;
            
            /**
             * Get the next buffer.
             */
            virtual Buffer getBuffer()=0;
            
            /**
             * Decoder loaded the file
             */
            virtual bool isLoaded()=0;
            
            /**
             * Decoder is in a valid state
             */
            virtual bool isValid()=0;
            
            /**
             * The duration of the audio file in seconds.
             */
            virtual float duration()=0;
            
            /**
             * The size of the audio file in bytes
             */
            virtual int size()=0;
            
            /**
             * Is the file a stereo sound?
             */
            virtual bool isStereo()=0;
            
            /**
             * Is the decoder finished with decoding the file?
             */
            virtual bool isEndOfFile()=0;
    };
}

#endif // GLUON_AUDIO_DECODER_H
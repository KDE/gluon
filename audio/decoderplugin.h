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

#ifndef GLUON_AUDIO_DECODERPLUGIN_H
#define GLUON_AUDIO_DECODERPLUGIN_H

#include <QtCore/QObject>

#include "gluon_audio_export.h"

namespace GluonAudio
{
    class Decoder;
    
    /**
     * A Decoder plugin creates new instances of the decoder of this plugin.
     */
    class GLUON_AUDIO_EXPORT DecoderPlugin : public QObject
    {
            Q_OBJECT
        public:
            DecoderPlugin(QObject* parent=0);
            virtual ~DecoderPlugin();
            
            /**
             * Create a new decoder instance to decode the given fileName.
             */
            virtual Decoder* createDecoder(QString fileName)=0;
    };
}

#define GLUON_DECODER_PLUGIN(_file) Q_PLUGIN_METADATA(IID "org.kde.gluon.audio.decoder" FILE #_file)

#endif // GLUON_AUDIO_DECODERPLUGIN_H
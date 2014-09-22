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

#ifndef GLUON_AUDIO_AUDIOHELPER_H
#define GLUON_AUDIO_AUDIOHELPER_H

#include "gluon_audio_export.h"

#include <core/singleton.h>

namespace GluonAudio
{
    class AbstractFile;
    class MusicFile;
    class EffectFile;
    class Source;
    class DecoderPlugin;
    
    /**
     * A Singleton with a view helper functions for GluonAudio classes.
     */
    class GLUON_AUDIO_EXPORT AudioHelper: public GluonCore::Singleton<AudioHelper>
    {
            Q_OBJECT
            GLUON_SINGLETON( AudioHelper )
        public:
            /**
             * Register the file object. The update function of registered objects will be called regularly.
             */
            void registerForUpdates( AbstractFile* file );
            
            /**
             * Unregister the file object, so it won't get update calls anymore.
             */
            void unregisterForUpdates( AbstractFile* file );
            
            void registerForUpdates( Source* source );
            void unregisterForUpdates( Source* source );
            
            /**
             * Get a list of decoder plugins.
             */
            QList<DecoderPlugin*> decoderPlugins();
            
            /**
             * Create an audio file object. If there already is an object for this path, it will be returned instead.
             */
            AbstractFile* getAudioFile( QString path );
            
            /**
             * Creates a MusicFile object. If a MusicFile object already exists for this path, return that one. If there is an open
             * EffectFile for this path, return 0.
             */
            MusicFile* getMusicFile( QString path );
            
            /**
             * Creates an EffectFile object. If an EffectFile object already exists for this path, return that one. If there is an open
             * MusicFile for this path, return 0.
             */
            EffectFile* getEffectFile( QString path );
            
        protected:
            void timerEvent(QTimerEvent* event);
            
        private:
            ~AudioHelper();
            
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_AUDIOHELPER_H
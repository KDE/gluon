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

#ifndef GLUONAUDIO_LINEARPLAYLIST_H
#define GLUONAUDIO_LINEARPLAYLIST_H

#include "../abstractplaylist.h"
#include "../gluon_audio_export.h"

namespace GluonAudio
{
    class AbstractFile;
    
    /**
     * Plays a list of files linear.
     */
    class GLUON_AUDIO_EXPORT LinearPlaylist: public AbstractPlaylist
    {
            Q_OBJECT
        public:
            LinearPlaylist(QObject* parent=0);
            ~LinearPlaylist();
            
            /**
             * Set the list of files to play.
             */
            void setFiles( QList<AbstractFile*> files );
            
            /**
             * Should the next file be chosen randomly?
             */
            bool random();
            
            /**
             * Set whether the next files will be chosen randomly from the provided list.
             */
            void setRandom( bool random );
            
            /**
             * Returns whether the playlist starts again at the beginning after the last file was played.
             */
            bool repeatAll();
            
            /**
             * Set whether the playlist should start from the beginning after the last file.
             */
            void setRepeatAll( bool repeat );
            
            void removedFromSource(Source* source);
            
            void fileNearlyFinished();
            
        public slots:
            void start();
            void stop();
            
        private:
            class Private;
            Private* d;
    };
}           

#endif // GLUONAUDIO_LINEARPLAYLIST_H
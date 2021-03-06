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

#ifndef GLUONAUDIO_SINGLEFILE_H
#define GLUONAUDIO_SINGLEFILE_H

#include "../abstractplaylist.h"
#include "../gluon_audio_export.h"

#include <QtCore/QString>

namespace GluonAudio
{
    class AbstractFile;
    
    /**
     * Plays a single file and stops after that.
     */
    class GLUON_AUDIO_EXPORT SingleFile: public AbstractPlaylist
    {
            Q_OBJECT
        public:
            SingleFile(QObject* parent=0);
            ~SingleFile();
            
            /**
             * Set the file to play
             */
            void setFile( AbstractFile* file );
            void setFile( QString path );
            
            void removedFromSource( Source* source );
            
            void fileNearlyFinished();
            
            /**
             * Does this playlist repeat the file?
             */
            bool repeat() const;
            
            /**
             * Set whether the playlist should repeat playing the file whenever it finishes.
             */
            void setRepeat( bool repeat );
            
        public slots:
            void start();
            void stop();
            
        private:
            class Private;
            Private* d;
    };
}           

#endif // GLUONAUDIO_SINGLEFILE_H
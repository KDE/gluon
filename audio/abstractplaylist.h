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

#ifndef GLUONAUDIO_ABSTRACTPLAYLIST_H
#define GLUONAUDIO_ABSTRACTPLAYLIST_H

#include <QtCore/QObject>
#include "gluon_audio_export.h"

namespace GluonAudio
{
    class Source;
    
    /**
     * A gluon playlist is not just a list of files played after each other. It controls which file to play next.
     * Different subclasses define different ways to choose that next file.
     * 
     * Additionally, you control the playback (start, stop, pause) in this class.
     */
    class GLUON_AUDIO_EXPORT AbstractPlaylist : public QObject
    {   
            Q_OBJECT
        public:
            enum PlayingState { Started, Stopped, Paused };
            
            AbstractPlaylist( QObject* parent=0 );
            virtual ~AbstractPlaylist();
            
            /**
             * Called shortly before the source runs out of buffer. Choose a next file to play or call aboutToStop(),
             * if you want to stop after this file.
             */
            virtual void fileNearlyFinished()=0;
            
            /**
             * Informs you that this playlist instance was added to the given source.
             */
            virtual void addedToSource( Source* source );
            
            /**
             * Informs you that this playlist instance was removed from the given source. Stop all data streaming to this
             * source.
             */
            virtual void removedFromSource( Source* source );
            
            /**
             * Get the current playing state of this playlist.
             */
            virtual PlayingState getPlayingState() const;
            
        public slots:
            
            /**
             * Start playing the playlist or continue after the playlist was paused.
             */
            virtual void start()=0;
            
            /**
             * Pause the playback of this playlist.
             */
            virtual void pause();
            
            /**
             * Stop playing. This will stop the source, too.
             */
            virtual void stop();
            
            /**
             * This slot is called when the source ran out of buffer.
             */
            virtual void sourceOutOfBuffer(Source* s);
            
        signals:
            /**
             * The playlist finished playing.
             * 
             * @Note: This is not emitted if you called stop().
             */
            void stopped();
            
        protected:
            /**
             * The current source. May be 0.
             */
            Source* source() const;
            
            /**
             * Set the internal playing state.
             */
            void setPlayingState( PlayingState state );
            
            /**
             * Call this function if you want to stop playing after the current file.
             */
            void aboutToStop();
            
        private:
            class Private;
            Private* d;
            
    };
}

#endif // GLUONAUDIO_ABSTRACTPLAYLIST_H
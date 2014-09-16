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

namespace GluonAudio
{
    class Source;
    
    class AbstractPlaylist : public QObject
    {   
            Q_OBJECT
        public:
            enum PlayingState { Started, Stopped, Paused };
            
            AbstractPlaylist( QObject* parent=0 );
            virtual ~AbstractPlaylist();
            
            virtual void fileNearlyFinished()=0;
            
            virtual void addedToSource( Source* source );
            virtual void removedFromSource( Source* source );
            
            virtual PlayingState getPlayingState() const;
            
        public slots:
            virtual void start()=0;
            virtual void pause()=0;
            virtual void stop()=0;
            
            virtual void sourceOutOfBuffer(Source* s);
            
        signals:
            void stopped();
            
        protected:
            Source* source() const;
            
            void setPlayingState( PlayingState state );
            
        private:
            class Private;
            Private* d;
            
    };
}

#endif // GLUONAUDIO_ABSTRACTPLAYLIST_H
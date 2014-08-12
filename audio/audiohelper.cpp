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

#include "audiohelper.h"

#include <core/pluginregistry.h>

#include "audiofile.h"
#include "decoder.h"
#include "decoderplugin.h"

using namespace GluonAudio;

class AudioHelper::Private
{
    public:
        Private() : timerid(0) {}
        
        void loadPlugins();
        
        QList<DecoderPlugin*> plugins;
        QList<AudioFile*> registeredAudioFiles;
        int timerid;
};

void AudioHelper::Private::loadPlugins()
{
    QObjectList plugins = GluonCore::PluginRegistry::instance()->loadType( "org.kde.gluon.audio.decoder" );
    
    for( QObject* plugin : plugins )
    {
        DecoderPlugin* p = qobject_cast<DecoderPlugin*>(plugin);
        if(p)
            plugins.append(p);
    }
}

AudioHelper::AudioHelper(QObject* parent)
    : d(new Private())
{
    d->loadPlugins();
}

AudioHelper::~AudioHelper()
{
    delete d;
}

void AudioHelper::registerForUpdates(AudioFile* file)
{
    if( d->registeredAudioFiles.contains(file) )
        return;
    d->registeredAudioFiles.append(file);
    if( d->registeredAudioFiles.count() == 1 )
    {
        d->timerid = startTimer(100);
    }
}

void AudioHelper::unregisterForUpdates(AudioFile* file)
{
    if( d->registeredAudioFiles.removeOne(file) )
        if( d->registeredAudioFiles.count() == 0)
            killTimer(d->timerid);
}


QList< DecoderPlugin* > AudioHelper::decoderPlugins()
{
    return d->plugins;
}

void AudioHelper::timerEvent(QTimerEvent* event)
{
    for( AudioFile* file : d->registeredAudioFiles )
    {
        file->update();
    }
}




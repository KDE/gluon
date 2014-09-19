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
#include <core/log.h>

#include "abstractfile.h"
#include "source.h"
#include "decoder.h"
#include "decoderplugin.h"

using namespace GluonAudio;

GLUON_DEFINE_SINGLETON( AudioHelper )

class AudioHelper::Private
{
    public:
        Private() : fileTimer(0), sourceTimer(0) {}
        
        void loadPlugins();
        
        QList<DecoderPlugin*> plugins;
        QList<AbstractFile*> registeredFiles;
        QList<Source*> registeredSources;
        int fileTimer;
        int sourceTimer;
};

void AudioHelper::Private::loadPlugins()
{
    QObjectList qobjects = GluonCore::PluginRegistry::instance()->loadType( "org.kde.gluon.audio.decoder" );
    
    for( QObject* plugin : qobjects )
    {
        DecoderPlugin* p = qobject_cast<DecoderPlugin*>(plugin);
        if(p)
            plugins.append(p);
    }
    INFO() << QString("%1 decoder plugins loaded.").arg(plugins.count());
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

void AudioHelper::registerForUpdates(AbstractFile* file)
{
    if( d->registeredFiles.contains(file) )
        return;
    d->registeredFiles.append(file);
    if( d->registeredFiles.count() == 1 )
    {
        d->fileTimer = startTimer(30);
    }
}

void AudioHelper::unregisterForUpdates(AbstractFile* file)
{
    if( d->registeredFiles.removeOne(file) )
        if( d->registeredFiles.count() == 0)
            killTimer(d->fileTimer);
}

void AudioHelper::registerForUpdates(Source* source)
{
    if( d->registeredSources.contains( source ) )
        return;
    d->registeredSources.append(source);
    if( d->registeredSources.count() == 1 )
    {
        d->sourceTimer = startTimer(200);
    }
}

void AudioHelper::unregisterForUpdates(Source* source)
{
    if( d->registeredSources.removeOne(source) )
        if( d->registeredSources.count() == 0 )
            killTimer( d->sourceTimer );
}

QList< DecoderPlugin* > AudioHelper::decoderPlugins()
{
    return d->plugins;
}

void AudioHelper::timerEvent(QTimerEvent* event)
{
    if( event->timerId() == d->fileTimer )
    {
        for( AbstractFile* file : d->registeredFiles )
        {
            file->update();
        }
    }
    else if( event->timerId() == d->sourceTimer )
    {
        for( Source* source : d->registeredSources )
        {
            source->update();
        }
    }
}




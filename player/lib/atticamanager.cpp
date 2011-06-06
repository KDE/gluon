/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "atticamanager.h"

#include <attica/content.h>
#include <attica/listjob.h>

#include <QtCore/QDebug>

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON( AtticaManager )

AtticaManager::AtticaManager()
{
    connect( &m_manager, SIGNAL( defaultProvidersLoaded() ), SLOT( providersUpdated() ) );
    m_manager.loadDefaultProviders();
}

AtticaManager::~AtticaManager()
{
}

bool AtticaManager::isProviderValid()
{
    return m_provider.isValid();
}

Attica::Provider AtticaManager::provider()
{
    return m_provider;
}

void AtticaManager::providersUpdated()
{
    if( !m_manager.providers().isEmpty() )
    {
        m_provider = m_manager.providerByUrl( QUrl( "https://api.opendesktop.org/v1/" ) );
        if( !m_provider.isValid() )
        {
            emit failedToFetchProvider();
        }
        else
        {

            emit gotProvider();
        }
    }
}

bool AtticaManager::downloadGame( const QString& id )
{
    if( isDownloading )
    {
        return false;
    }

    isDownloading = true;
    m_currentId = id;
    if( AtticaManager::instance()->isProviderValid() )
    {
        requestContent();
    }
    else
    {
        connect( this, SIGNAL( gotProvider() ), SLOT( requestContent() ) );
    }

    return true;
}

void AtticaManager::requestContent()
{
    if( isProviderValid() )
    {
        Attica::ItemJob<Attica::Content> *job = provider().requestContent( m_currentId );
        connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
        job->start();
    }
    else
    {
        qDebug() << "No providers found.";
    }
}

void AtticaManager::processFetchedGameDetails( Attica::BaseJob* job )
{
    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content> *>( job );
    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        qDebug() << "It should be downloaded " << contentJob->result().downloadUrlDescription( 1 ).link();
    }
    else
    {
        qDebug() << "Could not fetch information";
    }
}

#include "atticamanager.moc"


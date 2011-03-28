/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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


#include "gamedownloadmanager.h"

#include "atticamanager.h"

#include <QtCore/QDebug>

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON(GameDownloadManager)

GameDownloadManager::GameDownloadManager() 
	: alreadyDownloading(false)
{
}

bool GameDownloadManager::addDownload ( const QString &id )
{
    if (alreadyDownloading) 
	{
        return false;
    }

    alreadyDownloading = true;
    m_id = id;
    if( AtticaManager::instance()->isProviderValid() )
    {
        providersUpdated();
    }
    else
    {
        connect( AtticaManager::instance(), SIGNAL( gotProvider() ), SLOT( providersUpdated() ) );
    }

    return true;
}

void GameDownloadManager::providersUpdated()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        Attica::ItemJob<Attica::Content> *job =
            AtticaManager::instance()->provider().requestContent(m_id);
        connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
        job->start();
    }
    else
    {
        qDebug() << "No providers found.";
    }
}

void GameDownloadManager::processFetchedGameDetails(Attica::BaseJob* job)
{
    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content> *>( job );
    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        qDebug() << "WE SHOULD DOWNLOAD " << contentJob->result().downloadUrlDescription(1).link();
    }
    else
    {
        qDebug() << "Could not fetch information";
    }
}

#include "gamedownloadmanager.moc"

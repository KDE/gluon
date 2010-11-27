/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

using namespace GluonPlayer;

template<> AtticaManager* GluonCore::Singleton<AtticaManager>::m_instance = 0;

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

#include "atticamanager.moc"


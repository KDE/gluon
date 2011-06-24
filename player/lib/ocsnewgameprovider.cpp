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

#include "ocsnewgameprovider.h"

#include <attica/provider.h>
#include <attica/content.h>

using namespace GluonPlayer;

class OcsNewGameProvider::Private
{
    public:
        Private() { }

        Attica::Provider* provider;
        QString gameCategory;
        QString gameName;
};

OcsNewGameProvider::OcsNewGameProvider( Attica::Provider* provider, const QString& gameCategory,
                                        const QString& gameName, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
    d->gameName = gameName;
}

OcsNewGameProvider::~OcsNewGameProvider()
{
    delete d;
}

void OcsNewGameProvider::addNewGame()
{
    Attica::Category category;
    category.setId( d->gameCategory );

    Attica::Content content;
    content.setName( d->gameName );

    Attica::ItemPostJob<Attica::Content> *job = d->provider->addNewContent( category, content );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( addNewGameComplete( Attica::BaseJob* ) ) );
    job->start();
}

void OcsNewGameProvider::addNewGameComplete( Attica::BaseJob* baseJob )
{
    Attica::ItemPostJob<Attica::Content>* job = static_cast<Attica::ItemPostJob<Attica::Content>*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        finished( job->result().id() );
    }
    else
    {
        emit failed();
    }
}

#include "ocsnewgameprovider.moc"

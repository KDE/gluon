/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "addgamejob.h"

#include <attica/provider.h>
#include <attica/content.h>

using namespace GluonPlayer;

class AddGameJob::Private
{
    public:
        QString gameCategory;
        QString gameName;

        QString id;
};

AddGameJob::AddGameJob( Attica::Provider* provider, const QString& gameCategory,
                        const QString& gameName, QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private )
{
    d->gameCategory = gameCategory;
    d->gameName = gameName;
}

AddGameJob::~AddGameJob()
{
    delete d;
}

void AddGameJob::startSocialService()
{
    Attica::Category category;
    category.setId( d->gameCategory );

    Attica::Content content;
    content.setName( d->gameName );

    Attica::ItemPostJob<Attica::Content> *job = provider()->addNewContent( category, content );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(addGameComplete(Attica::BaseJob*)) );
    job->start();
}

void AddGameJob::addGameComplete( Attica::BaseJob* baseJob )
{
    Attica::ItemPostJob<Attica::Content>* job = static_cast<Attica::ItemPostJob<Attica::Content>*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        d->id = job->result().id();
        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant AddGameJob::data()
{
    return d->id;
}

 

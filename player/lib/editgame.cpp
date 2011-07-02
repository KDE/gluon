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

#include "editgame.h"

#include <attica/provider.h>
#include <attica/content.h>

using namespace GluonPlayer;

class EditGame::Private
{
    public:
        Private() { }

        Attica::Provider* provider;
        QString id;
        Attica::Content existingContent;

        QString category;
        QString name;
        QString version;
        QString description;
        QString changelog;
        QString license;
        QString homepage;
};

EditGame::EditGame( Attica::Provider* provider, const QString& id, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
    d->id = id;
}

EditGame::~EditGame()
{
    delete d;
}

void EditGame::startFetchingExistingGame()
{
    Attica::ItemJob<Attica::Content> *job = d->provider->requestContent( d->id );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
    job->start();
}

void EditGame::processFetchedGameDetails( Attica::BaseJob* job )
{
    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content>*>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        d->existingContent = contentJob->result();
        fetchedExistingGame( d->id );
    }
    else
    {
        emit failed( d->id );
    }
}

void EditGame::startEditionUpload()
{
    if( !d->existingContent.isValid() )
    {
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( startEditionUpload() ) );
        return;
    }

    Attica::Category category;
    category.setId( d->category.isEmpty() ? "4440" : d->category );

    Attica::ItemPostJob<Attica::Content> *job = d->provider->editContent( category, d->id, d->existingContent );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( editingComplete( Attica::BaseJob* ) ) );
    job->start();
}

void EditGame::editingComplete( Attica::BaseJob* job )
{
    Attica::ItemPostJob<Attica::Content> *contentJob = static_cast<Attica::ItemPostJob<Attica::Content>*>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        emit finished( d->id );
    }
    else
    {
        emit failed( d->id );
    }
}

void EditGame::setCategory( const QString& categoryId )
{
    //TODO: Check that category is Gluon
    d->category = categoryId;
}

void EditGame::setChangelog( const QString& changelog )
{
    d->changelog = changelog;
    applyChangelog();
}

void EditGame::setDescription( const QString& description )
{
    d->description = description;
    applyDescription();
}

void EditGame::setLicense( const QString& licenseId )
{
    d->license = licenseId;
    applyLicense();
}

void EditGame::setName( const QString& name )
{
    d->name = name;
    applyName();
}

void EditGame::setVersion( const QString& version )
{
    d->version = version;
    applyVersion();
}

void EditGame::setHomepage( const QString& homepage )
{
    d->homepage = homepage;
}

void EditGame::applyChangelog()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "changelog", d->changelog );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyChangelog() ) );
}

void EditGame::applyDescription()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "description", d->description );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyDescription() ) );
}

void EditGame::applyLicense()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "licensetype", d->license );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyLicense() ) );
}

void EditGame::applyName()
{
    if( d->existingContent.isValid() )
        d->existingContent.setName( d->name );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyName() ) );
}

void EditGame::applyVersion()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "version", d->version );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyVersion() ) );
}

void EditGame::applyHomepage()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "homepage", d->homepage );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyHomepage() ) );
}

#include "editgame.moc"

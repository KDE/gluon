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

#include "editgamejob.h"

#include <attica/provider.h>
#include <attica/content.h>

using namespace GluonPlayer;

class EditGameJob::Private
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
        QString downloadType;
        QString downloadPrice;
        QString downloadLink;
        QString downloadName;
};

EditGameJob::EditGameJob( Attica::Provider* provider, const QString& id, QObject* parent )
    : AbstractSocialServicesJob( provider ), d( new Private() )
{
    d->provider = provider;
    d->id = id;

    startFetchingExistingGame();
}

EditGameJob::~EditGameJob()
{
    delete d;
}

void EditGameJob::startSocialService()
{
    startEditionUpload();
}

void EditGameJob::startFetchingExistingGame()
{
    Attica::ItemJob<Attica::Content> *job = d->provider->requestContent( d->id );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
    job->start();
}

void EditGameJob::processFetchedGameDetails( Attica::BaseJob* job )
{
    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content>*>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        d->existingContent = contentJob->result();
        emit fetchedExistingGame( d->id );
    }
    else
    {
        emitFailed();
    }
}

void EditGameJob::startEditionUpload()
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

void EditGameJob::editingComplete( Attica::BaseJob* job )
{
    Attica::ItemPostJob<Attica::Content> *contentJob = static_cast<Attica::ItemPostJob<Attica::Content>*>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

void EditGameJob::setCategory( const QString& categoryId )
{
    //TODO: Check that category is Gluon
    d->category = categoryId;
    applyCategory();
}

void EditGameJob::setChangelog( const QString& changelog )
{
    d->changelog = changelog;
    applyChangelog();
}

void EditGameJob::setDescription( const QString& description )
{
    d->description = description;
    applyDescription();
}

void EditGameJob::setLicense( const QString& licenseId )
{
    d->license = licenseId;
    applyLicense();
}

void EditGameJob::setName( const QString& name )
{
    d->name = name;
    applyName();
}

void EditGameJob::setVersion( const QString& version )
{
    d->version = version;
    applyVersion();
}

void EditGameJob::setHomepage( const QString& homepage )
{
    d->homepage = homepage;
    applyHomepage();
}

void EditGameJob::setDownloadType( const QString& downloadType )
{
    d->downloadType = downloadType;
    applyDownloadType();
}

void EditGameJob::setDownloadPrice( const QString& downloadPrice )
{
    d->downloadPrice = downloadPrice;
    applyDownloadPrice();
}

void EditGameJob::setDownloadLink( const QString& downloadLink )
{
    d->downloadLink = downloadLink;
    applyDownloadLink();
}

void EditGameJob::setDownloadName( const QString& downloadName )
{
    d->downloadName = downloadName;
    applyDownloadName();
}

void EditGameJob::applyCategory()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "typeid", d->category );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyCategory()) );
}

void EditGameJob::applyChangelog()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "changelog", d->changelog );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyChangelog() ) );
}

void EditGameJob::applyDescription()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "description", d->description );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyDescription() ) );
}

void EditGameJob::applyLicense()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "licensetype", d->license );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyLicense() ) );
}

void EditGameJob::applyName()
{
    if( d->existingContent.isValid() )
        d->existingContent.setName( d->name );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyName() ) );
}

void EditGameJob::applyVersion()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "version", d->version );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyVersion() ) );
}

void EditGameJob::applyHomepage()
{
    if( d->existingContent.isValid() )
    {
        d->existingContent.addAttribute( "homepage", d->homepage );
        d->existingContent.addAttribute( "homepagetype", "500" );
    }
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyHomepage() ) );
}

void EditGameJob::applyDownloadType()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "downloadtyp1", d->downloadType );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyDownloadType() ) );
}

void EditGameJob::applyDownloadPrice()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "downloadprice1", d->downloadPrice );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyDownloadPrice() ) );
}

void EditGameJob::applyDownloadLink()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "downloadlink1", d->downloadLink );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyDownloadLink() ) );
}

void EditGameJob::applyDownloadName()
{
    if( d->existingContent.isValid() )
        d->existingContent.addAttribute( "downloadname1", d->downloadName );
    else
        connect( this, SIGNAL( fetchedExistingGame( QString ) ), SLOT( applyDownloadName() ) );
}

QVariant EditGameJob::data()
{
    return d->id;
}

#include "editgamejob.moc"

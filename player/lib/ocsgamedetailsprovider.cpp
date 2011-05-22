/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "ocsgamedetailsprovider.h"

#include <attica/listjob.h>
#include <attica/content.h>
#include <attica/provider.h>
#include <attica/downloaditem.h>

#include <QStringList>
#include <QDebug>
#include "ocsprovider.h"

using namespace GluonPlayer;

class OcsGameDetails::Private
{
public:
    Private()   { }

    QString gameName;
    QString gameDescription;
    QString projectDirName;
    QString projectFileName;
    QStringList screenshotUrls;
    Status status;
    QString id;
};

OcsGameDetails::OcsGameDetails (const QString& gameName, const QString& gameDescription,
                                const QString& projectDirName, const QString& projectFileName,
                                const QStringList& screenshotUrls, Status status, const QString id,
                                QObject* parent) : QObject (parent), d (new Private())
{
    d->gameName = gameName;
    d->gameDescription = gameDescription;
    d->projectDirName = projectDirName;
    d->projectFileName = projectFileName;
    d->screenshotUrls = screenshotUrls;
    d->status = status;
    d->id = id;
}

OcsGameDetails::~OcsGameDetails()
{
    delete d;
}

QString OcsGameDetails::gameDescription() const
{
    return d->gameDescription;
}

QString OcsGameDetails::gameName() const
{
    return d->gameName;
}

QString OcsGameDetails::id() const
{
    return d->id;
}

QString OcsGameDetails::projectDirName() const
{
    return d->projectDirName;
}

QString OcsGameDetails::projectFileName() const
{
    return d->projectFileName;
}

QStringList OcsGameDetails::screenshotUrls() const
{
    return d->screenshotUrls;
}

OcsGameDetails::Status OcsGameDetails::status() const
{
    return d->status;
}

class OcsGameDetailsProvider::Private
{
public:
    Private() : provider(0) { }

    Attica::Provider *provider;
};

OcsGameDetailsProvider::OcsGameDetailsProvider (Attica::Provider* provider, QObject* parent)
    : QObject (parent), d(new Private())
{
    d->provider = provider;
}

void OcsGameDetailsProvider::fetchGameList()
{
    QStringList gluonGamesCategories;
    gluonGamesCategories << "4400" << "4410" << "4420" << "4430" << "4440";
    Attica::Category::List categories;

    foreach (const QString & gluonCategory, gluonGamesCategories) {
        Attica::Category category;
        category.setId (gluonCategory);
        categories.append (category);
    }

    Attica::ListJob<Attica::Content> *job = d->provider->searchContents(categories);
    connect (job, SIGNAL (finished (Attica::BaseJob*)), SLOT (processFetchedGamesList (Attica::BaseJob*)));
    job->start();
}

void OcsGameDetailsProvider::processFetchedGamesList (Attica::BaseJob* job)
{
    qDebug() << "Game List Successfully Fetched from the server!";
    QList<OcsGameDetails*> list;

    Attica::ListJob<Attica::Content> *contentJob = static_cast<Attica::ListJob<Attica::Content> *>(job);
    if( contentJob->metadata().error() == Attica::Metadata::NoError ) {
        foreach(Attica::Content content, contentJob->itemList()) {
            OcsGameDetails *details = new OcsGameDetails(content.name(), content.description(), "", "",
                                                         QStringList(), OcsGameDetails::Downloadable, content.id());
            list.append(details);
            //Uncomment to test download, downloads to install dir/games/id
            //OcsProvider::instance()->downloadGame(details->id());
        }

        emit gameDetailsFetched(list);
    } else {
        emit failedToFetchGameDetails();
    }
}

#include "ocsgamedetailsprovider.moc"

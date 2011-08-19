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

#include "categorylistjob.h"

#include <attica/provider.h>

using namespace GluonPlayer;

class CategoryItem::Private
{
    public:
        Private() { }

        QString id;
        QString name;
};

CategoryItem::CategoryItem( const QString& id, const QString& name, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->name = name;
}

CategoryItem::~CategoryItem()
{
    delete d;
}

QString CategoryItem::name() const
{
    return d->name;
}

QString CategoryItem::id() const
{
    return d->id;
}

class CategoryListJob::Private
{
    public:
        QList<QObject*> categoryList;
};

CategoryListJob::CategoryListJob( Attica::Provider* provider, QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
}

CategoryListJob::~CategoryListJob()
{
    delete d;
}

void CategoryListJob::startSocialService()
{
    Attica::ListJob<Attica::Category> *job = provider()->requestCategories();
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedCategoryList( Attica::BaseJob* ) ) );
    job->start();
}

void CategoryListJob::processFetchedCategoryList( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Category> *categoriesJob = static_cast<Attica::ListJob<Attica::Category> *>( job );

    if( categoriesJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Category & category, categoriesJob->itemList() )
        {
            CategoryItem* newCategory = new CategoryItem( category.id(), category.name(), this );
            d->categoryList.append( newCategory );
        }

        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant CategoryListJob::data()
{
    return QVariant::fromValue( d->categoryList );
}

Q_DECLARE_METATYPE( QList<QObject*> )

#include "categorylistjob.moc"

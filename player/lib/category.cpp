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

#include "category.h"

#include <attica/provider.h>

using namespace GluonPlayer;

class CategoryItem::Private
{
    public:
        Private() { }

        QString id;
        QString categoryName;
};

CategoryItem::CategoryItem( const QString& id, const QString& categoryName, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->id = id;
    d->categoryName = categoryName;
}

CategoryItem::~CategoryItem()
{
    delete d;
}

QString CategoryItem::categoryName() const
{
    return d->categoryName;
}

QString CategoryItem::id() const
{
    return d->id;
}

class Category::Private
{
    public:
        Private() { }

        Attica::Provider* provider;
};

Category::Category( Attica::Provider* provider, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
}

Category::~Category()
{
    delete d;
}

void Category::fetchCategories()
{
    Attica::ListJob<Attica::Category> *job = d->provider->requestCategories();
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedCategories( Attica::BaseJob* ) ) );
    job->start();
}

void Category::processFetchedCategories( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Category> *categoriesJob = static_cast<Attica::ListJob<Attica::Category> *>( job );

    QList<CategoryItem*> categoryList;

    if( categoriesJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( Attica::Category category, categoriesJob->itemList() )
        {
            CategoryItem* newCategory = new CategoryItem( category.id(), category.name(), this );
            categoryList.append( newCategory );
        }

        emit categoriesFetched( categoryList );
    }
    else
    {
        emit failed();
    }
}

#include "category.moc"

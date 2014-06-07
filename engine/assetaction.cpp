/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "assetaction.h"

#include <QtGui/QIcon>

using namespace GluonEngine;

class AssetAction::Private
{
public:
    Private()
    { }

    QString name;
    QIcon icon;
};

AssetAction::AssetAction( const QString& name, QObject* parent )
    : QObject( parent ), d(new Private)
{
    d->name = name;
}

AssetAction::~AssetAction()
{
    delete d;
}

QIcon AssetAction::icon() const
{
    return d->icon;
}

void AssetAction::setIcon( const QIcon& icon )
{
    d->icon = icon;
    emit iconChanged();
}

QString AssetAction::name() const
{
    return d->name;
}

void AssetAction::setName( const QString& name )
{
    if(name != d->name) {
        d->name = name;
        emit nameChanged();
    }
}

void AssetAction::trigger()
{
    emit triggered();
}

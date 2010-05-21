/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "asset.h"
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QMimeData>

REGISTER_OBJECTTYPE(GluonEngine, Asset)

using namespace GluonEngine;

class GluonEngine::AssetPrivate
{
    public:
        AssetPrivate()
        {
            loaded = false;
            mime = 0;
        }

        QUrl file;
        bool loaded;
        QMimeData* mime;
};

Asset::Asset(QObject *parent)
        : GluonObject(parent)
{
    d = new AssetPrivate;
    d->mime = new QMimeData;
}

Asset::~Asset()
{
    delete d->mime;
    delete d;
}

void
Asset::setName(const QString& newName)
{
    QString oldName(name());

    GluonCore::GluonObject::setName(newName);

    // Rename the underlying file, if one exists...
    if (QDir::current().exists(d->file.toLocalFile()) && !d->file.isEmpty())
    {
        QUrl newFile(QString("Assets/%1.%2").arg(fullyQualifiedName()).arg(QFileInfo(d->file.toLocalFile()).completeSuffix()));
        if (QDir::current().rename(d->file.toLocalFile(), newFile.toLocalFile()))
        {
            setFile(newFile);
        }
    }
}

void
Asset::setFile(const QUrl &newFile)
{
    d->file = newFile;
    emit dataChanged();
}

QUrl
Asset::file() const
{
    return d->file;
}

const QMimeData*
Asset::data() const
{
    return d->mime;
}

const QList< AssetTemplate >
Asset::templates()
{
    QList<AssetTemplate> templates;
    return templates;
}

bool
Asset::isLoaded() const
{
    return d->loaded;
}

void
Asset::load()
{
    d->loaded = true;
}

QString
Asset::childrenToGDL(int indentLevel) const
{
    Q_UNUSED(indentLevel)
    // We do not recurse here - this allows the assets to handle their own
    // children
    return QString();
}

QMimeData*
Asset::mimeData() const
{
    return d->mime;
}

void
Asset::setLoaded(bool loaded)
{
    d->loaded = loaded;
}

#include "asset.moc"

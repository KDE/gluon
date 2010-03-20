/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

void Asset::setName(const QString& newName)
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

void Asset::setFile(const QUrl &newFile)
{
    d->file = newFile;
    emit dataChanged();
}

QUrl Asset::file() const
{
    return d->file;
}

const QMimeData* Asset::data() const
{
    return d->mime;
}

bool Asset::isLoaded() const
{
    return d->loaded;
}

void Asset::load()
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

QMimeData* Asset::mimeData() const
{
    return d->mime;
}

void Asset::setLoaded(bool loaded)
{
    d->loaded = loaded;
}

#include "asset.moc"

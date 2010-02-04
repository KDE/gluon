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

REGISTER_OBJECTTYPE(GluonEngine, Asset)

using namespace GluonEngine;

class GluonEngine::AssetPrivate
{
public:
    QUrl file;
};

Asset::Asset(QObject *parent)
    : GluonObject(parent)
{
    d = new AssetPrivate;
}

Asset::~Asset()
{
    delete d;
}

GluonCore::GluonObject* Asset::instantiate()
{
    return new Asset(this);
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

const QStringList
Asset::supportedMimeTypes() const
{
    // We return an empty list, as the Asset class itself supports no mimetypes
    return QStringList();
}

QString
Asset::childrenToGDL(int indentLevel) const
{
    Q_UNUSED(indentLevel)
    // We do not recurse here - this allows the assets to handle their own
    // children
    return QString();
}

#include "asset.moc"

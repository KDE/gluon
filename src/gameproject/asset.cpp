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
#include "assetprivate.h"

using namespace Gluon;

REGISTER_OBJECTTYPE(Asset)

Asset::Asset(QObject * parent)
    : GluonObject(parent)
{
    d = new AssetPrivate;
}

Asset::Asset(const Asset &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
}

Asset::~Asset()
{
}

GluonObject* Asset::instantiate()
{
    return new Asset(this);
}

void Asset::setFile(const QUrl &newFile)
{
    d->file = newFile;
    emit dataChanged(this);
}

QUrl Asset::file() const
{
    return d->file;
}

#include "asset.moc"

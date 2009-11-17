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

using namespace Gluon;

REGISTER_OBJECTTYPE(Asset)

class Gluon::AssetPrivate
{
public:
    QString file;
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

GluonObject* Asset::instantiate()
{
    return new Asset(this);
}

void Asset::setFile(const QString &newFile)
{
    d->file = newFile;
    emit dataChanged();
}

QString Asset::file() const
{
    return d->file;
}

QString
Asset::toGDL(int indentLevel) const
{
    // We do not recurse here - this allows the assets to handle their own
    // children
    return propertiesToGDL();
}

#include "asset.moc"

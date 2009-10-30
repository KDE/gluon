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

#include "gameproject.h"
#include "gameprojectprivate.h"
#include <QtCore/QStringList>

using namespace Gluon;

REGISTER_OBJECTTYPE(GameProject)

GameProject::GameProject(QObject * parent)
{
    d = new GameProjectPrivate;
}

GameProject::GameProject(const GameProject &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
}

GameProject::~GameProject()
{
}

GluonObject *
GameProject::findItemByName(QString qualifiedName)
{
    GluonObject * parentObject = this;
    GluonObject * foundChild = NULL;
    
    QStringList path = qualifiedName.split('.');
    QStringList::const_iterator constIterator;
    for (constIterator = path.constBegin(); constIterator != path.constEnd(); ++constIterator)
    {
        foundChild == NULL;
        foreach(QObject * child, parentObject->children())
        {
            if(qobject_cast<GluonObject*>(child)->name() == (*constIterator).toUtf8())
            {
                foundChild = qobject_cast<GluonObject*>(child);
                break;
            }
        }

        // Guard against trying to go into non-existent sub-trees
        if(foundChild == NULL)
            return NULL;

        if(constIterator != path.constEnd())
        {
            parentObject = foundChild;
            foundChild = NULL;
        }
    }
    return foundChild;
}

/******************************************************************************
 * Property Getter-setters
 *****************************************************************************/

QString
GameProject::description() const
{
    return d->description;
}
void
GameProject::setDescription(QString newDescription)
{
    d->description = newDescription;
}

QUrl
GameProject::homepage() const
{
    return d->homepage;
}
void
GameProject::setHomepage(QUrl newHomepage)
{
    d->homepage = newHomepage;
}

QList<QUrl>
GameProject::mediaInfo() const
{
    return d->mediaInfo;
}
void
GameProject::setMediaInfo(QList<QUrl> newMediaInfo)
{
    d->mediaInfo = newMediaInfo;
}

QUrl
GameProject::filename() const
{
    return d->filename;
}
void
GameProject::setFilename(QUrl newFilename)
{
    d->filename = newFilename;
}

GameObject *
GameProject::entryPoint() const
{
    return d->entryPoint;
}
void
GameProject::setEntryPoint(GameObject * newEntryPoint)
{
    d->entryPoint = newEntryPoint;
}

#include "gameproject.moc"

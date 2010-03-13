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

#include <core/gdlhandler.h>
#include <core/debughelper.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QMetaClassInfo>

REGISTER_OBJECTTYPE(GluonEngine, GameProject)
Q_DECLARE_METATYPE(GluonEngine::Scene*);

using namespace GluonEngine;

GameProject::GameProject(QObject * parent)
    : GluonObject(parent)
{
    d = new GameProjectPrivate;
    setGameProject(this);

    #warning Q_PROPERTY does not currently handle namespaced types - see bugreports.qt.nokia.com/browse/QTBUG-2151
    QVariant somethingEmpty;
    Scene *theObject = d->entryPoint;
    somethingEmpty.setValue<Scene*>(theObject);
    setProperty("entryPoint", somethingEmpty);
}

GameProject::GameProject(const GameProject &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
    setProperty("entryPoint", other.property("entryPoint"));
}

GameProject::~GameProject()
{
}

GluonCore::GluonObject *
GameProject::findItemByName(QString qualifiedName)
{
    DEBUG_FUNC_NAME
    DEBUG_TEXT(QString("Looking up %1").arg(qualifiedName));
    QStringList names = qualifiedName.split('/');
    if(names.at(0) == name())
        names.removeFirst();
    return GluonObject::findItemByNameInObject(names, this);
}

bool
GameProject::saveToFile() const
{
    // Run through everything first and save each of the saveable assets
    GameProjectPrivate::saveChildren(this);

    // Eventually, save self
    QFile *projectFile = new QFile(filename().toLocalFile());
    if(!projectFile->open(QIODevice::WriteOnly))
        return false;

    QList<const GluonObject*> thisProject;
    thisProject.append(this);

    QTextStream projectWriter(projectFile);
    projectWriter << GluonCore::GDLHandler::instance()->serializeGDL(thisProject);
    projectFile->close();

    delete(projectFile);
    return true;
}

bool
GameProject::loadFromFile()
{
    DEBUG_FUNC_NAME

    // change directory to the project path..
    DEBUG_TEXT(QString("Changing working directory to %1").arg(QFileInfo(filename().toLocalFile()).canonicalPath()));
    QDir::setCurrent(QFileInfo(filename().toLocalFile()).canonicalPath());
    setFilename(filename().toLocalFile());

    DEBUG_TEXT(QString("Loading project from %1").arg(QFileInfo(filename().toLocalFile()).fileName()));
    QFile *projectFile = new QFile(QFileInfo(filename().toLocalFile()).fileName());
    if(!projectFile->open(QIODevice::ReadOnly))
        return false;

    QTextStream projectReader(projectFile);
    QString fileContents = projectReader.readAll();
    projectFile->close();

    if(fileContents.isEmpty())
        return false;

    QList<GluonObject*> objectList = GluonCore::GDLHandler::instance()->parseGDL(fileContents, this->parent());
    if(objectList.count() > 0)
    {
        if(objectList[0]->metaObject())
        {
            // If the first object in the list is a GluonProject, then let's
            // adapt ourselves to represent that object...
            if(objectList[0]->metaObject()->className() == this->metaObject()->className())
            {
                DEBUG_TEXT("Project successfully parsed - applying to local instance");
                GameProject* loadedProject = qobject_cast<GameProject*>(objectList[0]);

                // First things first - clean ourselves out, all the children
                // and the media info list should be gone-ified
                qDeleteAll(this->children());

                // Reassign all the children of the newly loaded project to
                // ourselves...
                foreach(QObject* child, loadedProject->children())
                {
                    GluonObject* theChild = qobject_cast<GluonObject*>(child);
                    theChild->setParent(this);
                    theChild->setGameProject(this);
                }

                // Set all the interesting values...
                setName(loadedProject->name());

                // Copy accross all the properties
                const QMetaObject *metaobject = loadedProject->metaObject();
                int count = metaobject->propertyCount();
                for(int i = 0; i < count; ++i)
                {
                    QMetaProperty metaproperty = metaobject->property(i);
                    const QString theName(metaproperty.name());
                    if(theName == "objectName" || theName == "name")
                        continue;
                    setProperty(metaproperty.name(), loadedProject->property(metaproperty.name()));
                }

                // Then get all the dynamic ones (in case any such exist)
                QList<QByteArray> propertyNames = loadedProject->dynamicPropertyNames();
                foreach(QByteArray propName, propertyNames)
                    setProperty(propName, loadedProject->property(propName));

                // Sanitize me!
                this->sanitize();

                // Finally, get rid of the left-overs
                qDeleteAll(objectList);

                DEBUG_TEXT("Project loading successful!");
            }
            // Otherwise it is not a GluonProject, and should fail!
            else
            {
                DEBUG_TEXT(QString("First object loaded is not a Gluon::GameProject."));
                DEBUG_TEXT(QString("Type of loaded object:").arg(objectList[0]->metaObject()->className()));
                DEBUG_TEXT(QString("Name of loaded object:").arg(objectList[0]->name()));
                return false;
            }
        }
        else
            return false;
    }

    delete(projectFile);
    return true;
}

bool
GameProject::loadFromFile(QUrl filename)
{
    setFilename(filename);
    return loadFromFile();
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

Scene *
GameProject::entryPoint() const
{
//    return d->entryPoint;
    return property("entryPoint").value<Scene*>();
}

void
GameProject::setEntryPoint(Scene * newEntryPoint)
{
    d->entryPoint = newEntryPoint;
    QVariant theNewValue;
    theNewValue.setValue<Scene*>(newEntryPoint);
    setProperty("entryPoint", theNewValue);
}

#include "gameproject.moc"

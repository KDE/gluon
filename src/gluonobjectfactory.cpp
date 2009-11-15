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

#include "gluonobjectfactory.h"
#include "gluonobject.h"
#include "component.h"
#include "asset.h"

#include <QtCore/QDebug>
#include <QDir>
#include <QApplication>
#include <QPluginLoader>

using namespace Gluon;

template<> GluonObjectFactory* KSingleton<GluonObjectFactory>::m_instance = 0;

void
GluonObjectFactory::registerObjectType(GluonObject * newObjectType)
{
    if(newObjectType)
    {
        qDebug() << "Registering object type" << newObjectType->metaObject()->className();
        objectTypes[newObjectType->metaObject()->className()] = newObjectType;
    }
}

GluonObject *
GluonObjectFactory::instantiateObjectByName(const QString& objectTypeName)
{
    QString fullObjectTypeName = QString("Gluon::") + objectTypeName;
    if(objectTypes.find(fullObjectTypeName) != objectTypes.end())
    {
        return objectTypes.value(fullObjectTypeName)->instantiate();
    }
    return 0;
}

void
GluonObjectFactory::loadPlugins()
{
    QList<QDir> pluginDirs;
    
    QDir pluginDir(QApplication::applicationDirPath());
    
#if defined(Q_OS_WIN)
    if (pluginDir.dirName().tolower() == "debug" || pluginDir.dirName().tolower() == "release")
        pluginDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginDir.dirName() == "MacOS")
    {
        pluginDir.cdUp();
        pluginDir.cdUp();
        pluginDir.cdUp();
    }
#endif
    if(pluginDir.cd("plugins"))
        pluginDirs.append(pluginDir);
    
    if(pluginDir.cd("/usr/lib/gluon"))
        pluginDirs.append(pluginDir);
    
    // Always look in the current dir
    pluginDirs.append(QDir::current());
    
    if(pluginDir.cd(QDir::homePath() + "/gluonplugins"))
        pluginDirs.append(pluginDir);

    qDebug() << "Number of plugin locations:" << pluginDirs.count();
    foreach(const QDir &theDir, pluginDirs)
    {
        qDebug() << "Looking for pluggable components in:" << theDir.absolutePath();
        qDebug() << "Found" << (theDir.count() - 2) << "potential plugins. Attempting to load:";
        
        foreach (QString fileName, theDir.entryList(QDir::Files))
        {
            QPluginLoader loader(theDir.absoluteFilePath(fileName));
            if(Component* loaded = qobject_cast<Component*>(loader.instance()))
                m_pluggedComponents.append(loaded);
            else if(Asset* loaded = qobject_cast<Asset*>(loader.instance()))
                m_pluggedAssets.append(loaded);
            else
                qDebug() << loader.errorString();
        }
    }
}

#include "gluonobjectfactory.moc"

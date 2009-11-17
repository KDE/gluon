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

QStringList
GluonObjectFactory::objectTypeNames() const
{
    QStringList theNames;
    
    QHash<QString, GluonObject*>::const_iterator i;
    for (i = objectTypes.constBegin(); i != objectTypes.constEnd(); ++i)
        theNames << i.key();
    
    return theNames;
}

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
    QString fullObjectTypeName(objectTypeName);
    if(!objectTypeName.contains("::"))
         fullObjectTypeName = QString("Gluon::") + fullObjectTypeName;
    
    qDebug() << "Attempting to instantiate object of type " << fullObjectTypeName;
    
    if(objectTypes.keys().indexOf(fullObjectTypeName) > -1)
        return objectTypes[fullObjectTypeName]->instantiate();
    
    qDebug() << "Object type name not found in factory!";

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

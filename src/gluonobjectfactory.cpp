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
    if(!pluginDir.cd("plugins"))
        pluginDir.cd("/home/leinir/Documents/Uni/msc/btcomponents/build/lib");

    qDebug() << "Looking for pluggable components in:" << pluginDir.absolutePath();
    qDebug() << "Found" << (pluginDir.count() - 2) << "potential plugins. Attempting to load:";
    
    foreach (QString fileName, pluginDir.entryList(QDir::Files))
    {
        qDebug() << "Attempting to load plugin from" << pluginDir.absoluteFilePath(fileName);
        QPluginLoader loader(pluginDir.absoluteFilePath(fileName));
        if(Component* loaded = qobject_cast<Component*>(loader.instance()))
        {
            m_pluggedComponents.append(loaded);
        }
        else if(Asset* loaded = qobject_cast<Asset*>(loader.instance()))
        {
            m_pluggedAssets.append(loaded);
        }
        else
        {
            QObject* loaded = loader.instance();
            QString name;
            if(loaded != NULL)
            {
                if(loaded->metaObject() != NULL)
                    name = QString("object classname = ") + QString(loaded->metaObject()->className());
                else
                    name = "loaded's metaobject was null";
            }
            else
                name = "loaded was null";
            qDebug() << "No object type found in file (" << name <<")";
        }
    }
}

#include "gluonobjectfactory.moc"

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "gluonobjectfactory.h"
#include "gluonobject.h"
#include "debughelper.h"
#include "gluon_global.h"

#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtGui/QApplication>
#include <QVariant>

#include <QtCore/QDebug>

using namespace GluonCore;

template<> GLUON_CORE_EXPORT GluonObjectFactory* Singleton<GluonObjectFactory>::m_instance = 0;

QStringList
GluonObjectFactory::objectTypeNames() const
{
    QStringList theNames;

    QHash<QString, GluonObject*>::const_iterator i;
    for (i = m_objectTypes.constBegin(); i != m_objectTypes.constEnd(); ++i)
        theNames << i.key();

    return theNames;
}

QHash< QString, GluonObject* >
GluonObjectFactory::objectTypes() const
{
    return m_objectTypes;
}

const QHash<QString, int>
GluonObjectFactory::objectTypeIDs() const
{
    return m_objectTypeIDs;
}

QStringList
GluonObjectFactory::objectMimeTypes() const
{
    return m_mimeTypes.keys();
}

void
GluonObjectFactory::registerObjectType(GluonObject * newObjectType, int typeID)
{
    DEBUG_BLOCK
    if (newObjectType)
    {
        DEBUG_TEXT(QString("Registering object type %1 with typeID %2").arg(newObjectType->metaObject()->className()).arg(typeID));
        m_objectTypes[newObjectType->metaObject()->className()] = newObjectType;
        m_objectTypeIDs[newObjectType->metaObject()->className()] = typeID;

        foreach(const QString &mimetype, newObjectType->supportedMimeTypes())
        {
            DEBUG_TEXT(QString("Adding mimetype %1 to the index").arg(mimetype));
            m_mimeTypes[mimetype] = newObjectType->metaObject()->className();
        }
    }
    else
        DEBUG_TEXT(QString("Attempted to register a NULL object type"));
}

GluonObject *
GluonObjectFactory::instantiateObjectByName(const QString& objectTypeName)
{
    DEBUG_BLOCK
    QString fullObjectTypeName(objectTypeName);
    if (!objectTypeName.contains("::"))
        fullObjectTypeName = QString("Gluon::") + fullObjectTypeName;

    if (m_objectTypes.keys().indexOf(fullObjectTypeName) > -1)
        return m_objectTypes[fullObjectTypeName]->instantiate();

    DEBUG_TEXT(QString("Object type named %1 not found in factory!").arg(objectTypeName));

    return 0;
}

GluonObject*
GluonObjectFactory::instantiateObjectByMimetype(const QString& objectMimeType)
{
    return instantiateObjectByName(m_mimeTypes[objectMimeType]);
}

QVariant
GluonObjectFactory::wrapObject(const QVariant& original, GluonObject* newValue)
{
    QString type = original.typeName();

    if (type.endsWith('*'))
    {
        //Remove the * from the type
        type = type.left(type.length() - 1);
    }

    if (m_objectTypes.contains(type))
        return m_objectTypes[type]->toVariant(newValue);

    return QVariant();
}

QVariant
GluonObjectFactory::wrapObject(const QString& type, GluonObject* newValue)
{
    DEBUG_BLOCK
    QString typeName = type;
    if (type.endsWith('*'))
        typeName = type.left(type.length() - 1);

    if (m_objectTypes.contains(typeName))
    {
        return m_objectTypes[typeName]->toVariant(newValue);
    }

    DEBUG_TEXT(QString("Warning: Type %1 not found.").arg(typeName));

    return QVariant();
}

void
GluonObjectFactory::loadPlugins()
{
    DEBUG_FUNC_NAME
    QList<QDir> pluginDirs;

    QDir pluginDir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginDir.dirName().tolower() == "debug" || pluginDir.dirName().tolower() == "release")
        pluginDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginDir.dirName() == "MacOS")
    {
        pluginDir.cdUp();
    }
#endif
    if (pluginDir.cd("PlugIns"))
        pluginDirs.append(pluginDir);

    if (pluginDir.cd(GluonCore::Global::libDirectory()))
        pluginDirs.append(pluginDir);

    if (pluginDir.cd(GluonCore::Global::libDirectory() + "/gluon"))
        pluginDirs.append(pluginDir);

    if (pluginDir.cd(QDir::homePath() + "/gluonplugins"))
        pluginDirs.append(pluginDir);

    DEBUG_TEXT(QString("Number of plugin locations: %1").arg(pluginDirs.count()));
    foreach(QDir theDir, pluginDirs)
    {
        DEBUG_TEXT(QString("Looking for pluggable components in %1").arg(theDir.absolutePath()));
        DEBUG_TEXT(QString("Found %1 potential plugins. Attempting to load...").arg(theDir.count() - 2));
        
        #ifdef Q_WS_X11
        //Only attempt to load our current version. This makes it possible to have different versions
        //of the plugins in the plugin dir.
        theDir.setNameFilters(QStringList() << QString("*.so.%1.%2.%3").arg(GLUON_VERSION_MAJOR).arg(GLUON_VERSION_MINOR).arg(GLUON_VERSION_PATCH));
        #endif
        foreach(const QString &fileName, theDir.entryList(QDir::Files))
        {
            // Don't attempt to load non-gluon_plugin prefixed libraries
            if (!fileName.contains("gluon"))
                continue;

            // Don't attempt to load non-libraries
            if (!QLibrary::isLibrary(theDir.absoluteFilePath(fileName)))
                continue;

            QPluginLoader loader(theDir.absoluteFilePath(fileName));
            loader.load();

            if (!loader.isLoaded())
            {
                DEBUG_TEXT(loader.errorString());
            }
        }
    }
}

#include "gluonobjectfactory.moc"

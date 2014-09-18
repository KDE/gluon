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

#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QVariant>
#include <QtCore/QJsonArray>
#include <QtCore/QSet>

#include "directoryprovider.h"
#include "gluonobject.h"
#include "debughelper.h"
#include "pluginregistry.h"
#include "factoryplugin.h"
#include "log.h"

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( GluonObjectFactory )

class GluonObjectFactory::Private
{
public:
    QHash<QString, const QMetaObject*> objectTypes;
    QHash<QString, QString> mimeTypes;
    QHash<QString, QJsonObject> metaData;
    QSet< QString > loadedPlugins;
};

void GluonObjectFactory::registerObjectType( const QJsonObject& metaData, GluonObject* object )
{
    QString type = object->metaObject()->className();

    d->objectTypes[ type ] = object->metaObject();
    d->metaData[ type ] = metaData;

    for( auto mimetype : metaData.value( "mimeTypes" ).toArray() )
    {
        d->mimeTypes[ mimetype.toString() ] = type;
    }
}

QStringList
GluonObjectFactory::objectTypeNames() const
{
    QStringList theNames;

    QHash<QString, const QMetaObject*>::const_iterator i;
    for( i = d->objectTypes.constBegin(); i != d->objectTypes.constEnd(); ++i )
        theNames << i.key();

    return theNames;
}

QHash<QString, const QMetaObject*>
GluonObjectFactory::objectTypes() const
{
    return d->objectTypes;
}

QStringList
GluonObjectFactory::objectMimeTypes() const
{
    return d->mimeTypes.keys();
}

GluonObject*
GluonObjectFactory::instantiateObjectByName( const QString& objectTypeName )
{
    const QMetaObject* meta;
    if( ( meta = d->objectTypes.value( objectTypeName, 0 ) ) )
    {
        GluonObject* obj = qobject_cast<GluonObject*>( meta->newInstance() );
        if( obj )
        {
            return obj;
        }
        else
        {
            WARNING() << objectTypeName << " does not have its constructor marked Q_INVOKABLE";
            return 0;
        }
    }

    CRITICAL() << objectTypeName << " not found in factory!";

    return 0;
}

GluonObject*
GluonObjectFactory::instantiateObjectByMimetype( const QString& objectMimeType )
{
    return instantiateObjectByName( d->mimeTypes[objectMimeType] );
}

void
GluonObjectFactory::loadPlugins()
{
    DEBUG() << "Begin loading plugins";

    auto pluginNames = PluginRegistry::instance()->pluginNamesForType( "org.kde.gluon.core.factoryplugin" );
    for( auto plugin : pluginNames )
    {
        if( d->loadedPlugins.contains( plugin ) )
        {
            continue;
        }

        DEBUG() << "  Loading plugin " << plugin;

        QJsonObject metaData = PluginRegistry::instance()->metaData( plugin );
        FactoryPlugin* p = qobject_cast< FactoryPlugin* >( PluginRegistry::instance()->load( plugin ) );
        if( p )
        {
            for( auto object : p->typesToRegister() )
            {
                //Prevent multiple plugins from registering the same type
                if( d->objectTypes.contains( object->metaObject()->className() ) )
                {
                    continue;
                }

                DEBUG() << "    Registering type " << object->metaObject()->className();
                registerObjectType( metaData.value( "MetaData" ).toObject().value( object->metaObject()->className() ).toObject(), object );
            }
            delete p;
        }
        else
        {
            NOTICE() << "  Plugin " << plugin << " does not provide the right plugin object";
        }

        d->loadedPlugins.insert( plugin );
    }
}

QJsonObject GluonObjectFactory::metaData(const QString& type) const
{
    if( d->metaData.contains( type ) )
        return d->metaData.value( type );

    return QJsonObject();
}

GluonObjectFactory::~GluonObjectFactory()
{
    delete d;
}

GluonObjectFactory::GluonObjectFactory ( QObject* parent )
    : GluonCore::Singleton< GluonCore::GluonObjectFactory >( parent ), d{ new Private }
{
    GluonObject obj;
    registerObjectType( QJsonObject::fromVariantMap( QVariantMap{ { "icon", "folder" } } ), &obj );
}

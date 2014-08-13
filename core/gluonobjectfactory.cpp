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

#include "directoryprovider.h"
#include "gluonobject.h"
#include "debughelper.h"
#include "pluginregistry.h"
#include "factoryplugin.h"

#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QVariant>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( GluonObjectFactory )

class GluonObjectFactory::Private
{
public:
    QHash<QString, const QMetaObject*> objectTypes;
    QHash<QString, QString> mimeTypes;
    QHash<QString, QJsonObject> metaData;
};

void GluonObjectFactory::registerObjectType( const QJsonObject& metaData, GluonObject* object )
{
    QString type = object->metaObject()->className();

    DEBUG_BLOCK
    DEBUG_TEXT( QString( "Registering object type %1" ).arg( type ) );

    d->objectTypes[ type ] = object->metaObject();
    d->metaData[ type ] = metaData;

    QString mimetypenames;
    for( auto mimetype : object->supportedMimeTypes() )
    {
        mimetypenames.append( ' ' + mimetype );
        d->mimeTypes[ mimetype ] = type;
    }
    if( mimetypenames.length() > 0 )
    {
        DEBUG_TEXT( QString( "Added mimetypes %1 to the index" ).arg( mimetypenames ) )
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
    DEBUG_BLOCK
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
            DEBUG_TEXT2( "If you are seeing this message, you have most likely failed to mark the constructor of %1 as Q_INVOKABLE", objectTypeName )
            return 0;
        }
    }

    DEBUG_TEXT( QString( "Object type named %1 not found in factory!" ).arg( objectTypeName ) )

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
    auto pluginNames = PluginRegistry::instance()->pluginNamesForType( "org.kde.gluon.core.factoryplugin" );
    for( auto plugin : pluginNames )
    {
        QJsonObject metaData = PluginRegistry::instance()->metaData( plugin );
        FactoryPlugin* p = qobject_cast< FactoryPlugin* >( PluginRegistry::instance()->load( plugin ) );
        if( p )
        {
            for( auto object : p->typesToRegister() )
            {
                registerObjectType( metaData.value( "MetaData" ).toObject().value( object->metaObject()->className() ).toObject(), object );
            }

            delete p;
        }
    }
}

QJsonObject GluonObjectFactory::metaData(const QString& type) const
{
    if( d->metaData.contains( type ) )
        return d->metaData.value( type );

    return QJsonObject();
}

GluonObjectFactory::GluonObjectFactory ( QObject* parent )
    : GluonCore::Singleton< GluonCore::GluonObjectFactory >( parent )
{
    GluonObject obj;
    registerObjectType( QJsonObject(), &obj );
}

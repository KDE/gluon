/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "material.h"

#include <QtCore/QMetaProperty>

#include <core/gdlserializer.h>
#include <core/debughelper.h>

#include "materialinstance.h"
#include "technique.h"
#include "manager.h"
#include "backend.h"
#include "shader.h"

REGISTER_OBJECTTYPE( GluonGraphics, Material )

using namespace GluonGraphics;

class Material::Private
{
    public:
        Private() : shader( 0 ), instanceCount( 0 ) { }
        QHash<QString, Technique*> techniques;

        Shader* shader;

        int instanceCount;

        QHash< QString, MaterialInstance* > instances;
        QList< QPair< QString, QVariant > > defaultValues;
};

Material::Material( QObject* parent )
    : GluonObject( parent ), d( new Private )
{
}

Material::~Material()
{
    delete d;
}

bool Material::load( const QUrl& url )
{
    if( !url.isValid() )
        return false;

    if( d->shader )
    {
        delete d->shader;
        d->shader = 0;
        d->defaultValues.clear();
    }

    d->shader = Manager::instance()->backend()->createShader();

    GluonCore::GluonObjectList objects;
    if( !GluonCore::GDLSerializer::instance()->read( url, objects ) )
        return false;

    GluonCore::GluonObject* obj = objects.at( 0 );

    QList<QByteArray> properties = obj->dynamicPropertyNames();
    foreach( const QByteArray & propertyName, properties )
    {
        if( propertyName == "vertexShader" )
        {
            d->shader->setSource( Shader::VertexProgramSource, obj->property( propertyName ).toString() );
        }
        else if( propertyName == "fragmentShader" )
        {
            d->shader->setSource( Shader::FragmentProgramSource, obj->property( propertyName ).toByteArray() );
        }
        else
        {
            d->defaultValues.append( QPair< QString, QVariant >( propertyName, obj->property( propertyName ) ) );
        }
    }

    return true;
}

void Material::build( const QString& name )
{
    if( !d->shader )
        return;

    if( !d->shader->build() )
        debug( d->shader->error() );
}

Technique*
Material::technique( const QString& name ) const
{
    return 0;
}

void
Material::addTechnique( Technique* technique )
{

}

void
Material::removeTechnique( const QString& name )
{

}

void
Material::setDefaultTechnique( const QString& name )
{

}

MaterialInstance*
Material::createInstance( const QString& name )
{
    QString actualName = name.isEmpty() ? QString( "Instance_%1" ).arg( d->instanceCount++ ) : name;

    MaterialInstance* instance;
    if( !d->instances.contains( actualName ) )
    {
        instance = new MaterialInstance( this );
        instance->setMaterial( this );
        d->instances.insert( actualName, instance );

        QList< QPair< QString, QVariant > >::iterator itr;
        for( itr = d->defaultValues.begin(); itr != d->defaultValues.end(); ++itr )
        {
            instance->setProperty( (*itr).first.toUtf8(), (*itr).second );
        }
    }
    else
    {
        instance = d->instances.value( actualName );
    }
    return instance;
}

MaterialInstance*
Material::instance( const QString& name )
{
    if( d->instances.contains( name ) )
        return d->instances.value( name );

    return 0;
}

Shader* Material::shader()
{
    return d->shader;
}

#include "material.moc"

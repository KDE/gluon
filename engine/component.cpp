/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "component.h"
#include "componentprivate.h"
#include "gameobject.h"

#include "asset.h"

#include <core/debughelper.h>

#include <QtCore/QString>
#include <QtCore/QMetaProperty>

using namespace GluonEngine;

Component::Component( QObject* parent )
    : GluonObject( parent )
    , d( new ComponentPrivate )
{
}

Component::~Component()
{
    delete d;
}

QString
Component::category() const
{
    return QString( "Uncategorised" );
}

QVariant
Component::toVariant( GluonCore::GluonObject* wrapThis )
{
    if( QString::fromAscii( staticMetaObject.className() ).compare( "GluonCore::Component" ) )
    {
        DEBUG_BLOCK
        DEBUG_TEXT2( "Found attempt to use class without toVariant as property. Offending class: %1", staticMetaObject.className() )
    }
    return QVariant::fromValue<GluonEngine::Component*>( qobject_cast<GluonEngine::Component*>( wrapThis ) );
}

void
Component::update( int /* elapsedMilliseconds */ )
{
}

void
Component::draw( int /* timeLapse */ )
{
}

void
Component::sanitize()
{
    if( parent() )
    {
        if( parent()->metaObject() )
        {
            if( QString::compare( parent()->metaObject()->className(), "GameObject" ) )
            {
                GameObject* theParent = qobject_cast<GameObject*>( parent() );
                if( theParent )
                {
                    theParent->addComponent( this );
                    d->gameObject = theParent;
                }
            }
        }
    }
    GluonObject::sanitize();
}

// Property getter-setters

void
Component::setDescription( const QString& newDescription )
{
    d->description = newDescription;
}

QString
Component::description() const
{
    return d->description;
}

void
Component::setEnabled( bool newEnabled )
{
    d->enabled = newEnabled;
}

bool
Component::enabled() const
{
    return d->enabled;
}

GameObject*
Component::gameObject()
{
    return d->gameObject;
}

void
Component::setGameObject( GameObject* newGameObject )
{
    d->gameObject = newGameObject;
}

QString
Component::stringFromProperty( const QString& propertyName, const QString& indentChars ) const
{
    DEBUG_FUNC_NAME
    QMetaProperty prop = metaObject()->property( metaObject()->indexOfProperty( propertyName.toUtf8() ) );
    if( QString( prop.typeName() ) == QString( "GluonEngine::Asset*" ) )
    {
        GluonEngine::Asset* asset = prop.read( this ).value<GluonEngine::Asset*>();
        if( asset )
        {
            return QString( "\n%1%2 GluonEngine::Asset(%3)" ).arg( indentChars, propertyName, asset->fullyQualifiedName() );
        }
    }
    return GluonCore::GluonObject::stringFromProperty( propertyName, indentChars );
}

#include "component.moc"

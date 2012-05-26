/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_MANAGER_H
#define GLUONGRAPHICS_MANAGER_H

#include <QtCore/QHash>
#include <QtCore/QVariant>

#include <core/singleton.h>
#include <core/debughelper.h>

#include "gluon_graphics_export.h"

class QWidget;
namespace GluonGraphics
{
    class Backend;
    class World;

    class GLUON_GRAPHICS_EXPORT Manager : public GluonCore::Singleton< Manager >
    {
        Q_OBJECT
        GLUON_SINGLETON( Manager )

        public:
            struct Defaults
            {
                static const QString World;
                static const QString RenderTarget;
                static const QString Material;
                static const QString SpriteMesh;
            };

            Backend* backend();

            void initialize();

            World* createWorld( const QString& identifier = Defaults::World );
            World* world( const QString& identifier = Defaults::World ) const;
            void destroyWorld( const QString& identifier = Defaults::World );

            World* currentWorld() const;
            void setCurrentWorld( const QString& identifier );

            template < typename T >
            T* createResource( const QString& identifier );

            template < typename T >
            void addResource( const QString& identifier, T* object );

            template < typename T >
            T* resource( const QString& identifier ) const;

            template < typename T >
            void destroyResource( const QString& identifier );

            template < typename T >
            void destroyResource( T* resource );

        Q_SIGNALS:
            void currentWorldChanged();

        private:
            ~Manager();

            Q_PRIVATE_SLOT( d, void aboutToQuit() );

            class Private;
            Private* const d;

            QHash< QString, QObject* > m_resources;

            static const char* resourceIdentifierProperty;
    };

    #define PREFIX_IDENTIFIER(Object, Identifier) QString( "%1::%2" ).arg( T::staticMetaObject.className() ).arg( Identifier );

    template < typename T >
    T* Manager::createResource( const QString& identifier )
    {
        QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            return qobject_cast< T* >( m_resources.value( prefixedIdentifier ) );

        T* newResource = new T( this );
        m_resources.insert( prefixedIdentifier, newResource );
        newResource->setProperty( resourceIdentifierProperty, prefixedIdentifier );

        DEBUG_FUNC_NAME
        DEBUG_TEXT2( "Created resource %1", prefixedIdentifier );
        return newResource;
    }

    template < typename T >
    void Manager::addResource( const QString& identifier, T* object )
    {
        QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
        if( !m_resources.contains( prefixedIdentifier ) )
        {
            m_resources.insert( prefixedIdentifier, object );
            object->setProperty( resourceIdentifierProperty, prefixedIdentifier );

            DEBUG_FUNC_NAME
            DEBUG_TEXT2( "Added resource %1", prefixedIdentifier );
        }
    }

    template < typename T >
    T* Manager::resource( const QString& identifier ) const
    {
        QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            return qobject_cast< T*>( m_resources.value( prefixedIdentifier ) );

        return 0;
    }

    template < typename T >
    void Manager::destroyResource( const QString& identifier )
    {
        QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
        QObject* resource = m_resources.value( prefixedIdentifier );
        if( resource )
        {
            m_resources.remove( prefixedIdentifier );
            delete resource;

            DEBUG_FUNC_NAME
            DEBUG_TEXT2( "Destroyed resource %1", prefixedIdentifier );
        }
    }

    template < typename T >
    void Manager::destroyResource( T* resource )
    {
        QString prefixedIdentifier = resource->property( resourceIdentifierProperty ).toString();
        if( !prefixedIdentifier.isEmpty() && m_resources.contains( prefixedIdentifier ) )
        {
            QObject* resource = m_resources.value( prefixedIdentifier );
            m_resources.remove( prefixedIdentifier );
            resource->deleteLater();
        }
    }
}

#endif // GLUONGRAPHICS_MANAGER_H

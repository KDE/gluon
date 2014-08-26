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

    /**
     * A class to manage resources that should only exists once.
     *
     * The manager class is used to manage resources like textures and materials, objects of which only
     * one instance should ever be available.
     *
     * \TODO This should be moved to Core to make it available for other modules that need it. (Like Audio)
     */
    class GLUON_GRAPHICS_EXPORT Manager : public GluonCore::Singleton< Manager >
    {
            Q_OBJECT
            GLUON_SINGLETON( Manager )

        public:
            /**
             * Names for certain default objects that should always be available.
             */
            struct Defaults
            {
                static const QString World;
                static const QString RenderTarget;
                static const QString Material;
                static const QString SpriteMesh;
                static const QString Texture;
            };

            /**
             * \return An instance of Backend suitable for the current platform.
             */
            Backend* backend();

            /**
             * Initialize the default objects.
             */
            void initialize();

            /**
             * Create a new world.
             *
             * \sa World
             *
             * \param identifier The name of the world to create.
             *
             * \return A new instance of World or an existing instance if the named world already exists.
             */
            World* createWorld( const QString& identifier = Defaults::World );
            /**
             * Retrieve a world.
             *
             * \param identifier The name of the world to retrieve.
             *
             * \return The named world or 0 if the world does not exist.
             */
            World* world( const QString& identifier = Defaults::World ) const;
            /**
             * Destroy an instance of World.
             *
             * This will remove it from the internal list of worlds and delete the object after that. Any
             * entities contained in the world will also be destroyed.
             *
             * If the world does not exist, this will do nothing.
             *
             * \param identifier The name of the world to destroy.
             */
            void destroyWorld( const QString& identifier = Defaults::World );

            /**
             * \return The current active world.
             */
            World* currentWorld() const;
            /**
             * Set the current active world.
             *
             * \param identifier The name of the world to activate.
             *
             * \todo If we keep track of a Scene's world in Engine, this can be removed. It also means we
             * could move to a one-world-per-scene approach, avoiding some mess with creating/destroying objects
             * in scenes.
             */
            void setCurrentWorld( const QString& identifier );

            /**
             * Create a resource of type T identified by identifier.
             *
             * This will create an instance of T and add it to the internal list of resources Manager manages.
             *
             * \param identifier The identifier used to identify the resource.
             *
             * \return A new instance of T or an existing instance of T if it already exists.
             */
            template < typename T >
            T* createResource( const QString& identifier );

            /**
             * Add a resource to the list of managed resources.
             *
             * Note that this will do nothing if the resource already exists.
             *
             * \param identifier The identifier used to identify the resource.
             * \param object The object to add as resource.
             */
            template < typename T >
            void addResource( const QString& identifier, T* object );

            /**
             * Retrieve a resource.
             *
             * \param identifier The identifier used to identify the resource.
             *
             * \return The instance of the resource or 0 if it does not exist.
             */
            template < typename T >
            T* resource( const QString& identifier ) const;

            /**
             * Remove a resource from the list of managed resources.
             *
             * This will do nothing if the resource does not exist.
             *
             * \param identifier The identifier used to identify the resource.
             */
            template < typename T >
            void removeResource( const QString& identifier );

            /**
             * Destroy a managed resource.
             *
             * This will remove the resource from the list of managed resources,
             * then destroy that resource.
             *
             * If the resource does not exist, this method does nothing.
             *
             * \param identifier The identifier used to identify the resource.
             */
            template < typename T >
            void destroyResource( const QString& identifier );

            /**
             * Destroy a managed resource.
             *
             * This is an overloaded method.
             *
             * \param resource The resource to destroy.
             *
             * \sa destroyResource(const QString&)
             */
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

#define PREFIX_IDENTIFIER( Object, Identifier ) QString( "%1::%2" ).arg( T::staticMetaObject.className() ).arg( Identifier );

    template < typename T >
    T* Manager::createResource( const QString& identifier )
    {
        QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            return qobject_cast< T* >( m_resources.value( prefixedIdentifier ) );

        T* newResource = new T( this );
        m_resources.insert( prefixedIdentifier, newResource );
        newResource->setProperty( resourceIdentifierProperty, prefixedIdentifier );

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
    void Manager::removeResource( const QString& identifier )
    {
        QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            m_resources.remove( identifier );
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

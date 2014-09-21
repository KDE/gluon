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

#ifndef GLUONCORE_MANAGER_H
#define GLUONCORE_MANAGER_H

#include <type_traits>

#include <QtCore/QHash>
#include <QtCore/QVariant>

#include "singleton.h"
#include "debughelper.h"
#include "gluoncore_export.h"
#include "log.h"

namespace GluonCore
{
    class Backend;
    class World;

    /**
     * A class to manage resources that should only exists once.
     *
     * The resource manager class is used to manage resources like textures and audio files, data objects of which only
     * one instance should ever be available.
     *
     * This class is designed to be type-agnostic, with the only
     *
     */
    class GLUONCORE_EXPORT ResourceManager : public GluonCore::Singleton< ResourceManager >
    {
            Q_OBJECT
            GLUON_SINGLETON( ResourceManager )

        public:
            /**
             * Create a resource of type T identified by identifier.
             *
             * This will create an instance of T and add it to the internal list of resources managed.
             *
             * \param identifier The identifier used to identify the resource.
             *
             * \return A new instance of T or an existing instance of T if it already exists.
             *
             * \note T needs to be a QObject subclass and constructible with new T( QObject* ).
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
             *
             * \note T needs to be a QObject subclass.
             */
            template < typename T >
            void addResource( const QString& identifier, T* object );

            /**
             * Retrieve a resource.
             *
             * \param identifier The identifier used to identify the resource.
             *
             * \return The instance of the resource or nullptr if it does not exist.
             *
             * \note T needs to be a QObject subclass.
             */
            template < typename T >
            T* resource( const QString& identifier ) const;

            /**
             * Remove a resource from the list of managed resources.
             *
             * This will do nothing if the resource does not exist.
             *
             * \param identifier The identifier used to identify the resource.
             *
             * \note T needs to be a QObject subclass.
             */
            template < typename T >
            void removeResource( const QString& identifier );

            /**
             * Remove a resource from the list of managed resources.
             *
             * This is an overloaded method.
             *
             * \param resource The resource to remove.
             *
             * \sa removeResource(const QString&)
             */
            void removeResource( QObject* resource );

            /**
             * Destroy a managed resource.
             *
             * This will remove the resource from the list of managed resources,
             * then destroy that resource.
             *
             * If the resource does not exist, this method does nothing.
             *
             * \param identifier The identifier used to identify the resource.
             *
             * \note T needs to be a QObject subclass.
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
            void destroyResource( QObject* resource );

        private:
            friend class ResourceManagerTest;
            ~ResourceManager();
            template < typename T >
            static QString internalID( const QString& id );

            QHash< QString, QObject* > m_resources;
            static QByteArray resourceIdentifierProperty;
    };

    template < typename T >
    T* ResourceManager::createResource( const QString& identifier )
    {
        static_assert( std::is_base_of< QObject, T >::value, "Object must be a QObject subclass" );
        static_assert( std::is_constructible< T, QObject* >::value, "Object must be constructible with a QObject* parent" );
        Q_ASSERT( !identifier.isEmpty() );

        QString prefixedIdentifier = internalID< T >( identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            return qobject_cast< T* >( m_resources.value( prefixedIdentifier ) );

        T* newResource = new T( this );
        m_resources.insert( prefixedIdentifier, newResource );
        newResource->setProperty( resourceIdentifierProperty, prefixedIdentifier );

        return newResource;
    }

    template < typename T >
    void ResourceManager::addResource( const QString& identifier, T* object )
    {
        static_assert( std::is_base_of< QObject, T >::value, "Object must be a QObject subclass" );
        Q_ASSERT( !identifier.isEmpty() );

        QString prefixedIdentifier = internalID< T >( identifier );
        if( !m_resources.contains( prefixedIdentifier ) )
        {
            if( !m_resources.keys( object ).isEmpty() )
                return;

            m_resources.insert( prefixedIdentifier, object );
            object->setProperty( resourceIdentifierProperty, prefixedIdentifier );
        }
    }

    template < typename T >
    T* ResourceManager::resource( const QString& identifier ) const
    {
        static_assert( std::is_base_of< QObject, T >::value, "Object must be a QObject subclass" );
        Q_ASSERT( !identifier.isEmpty() );

        QString prefixedIdentifier = internalID< T >( identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            return qobject_cast< T* >( m_resources.value( prefixedIdentifier ) );

        return nullptr;
    }

    template < typename T >
    void ResourceManager::removeResource( const QString& identifier )
    {
        static_assert( std::is_base_of< QObject, T >::value, "Object must be a QObject subclass" );
        Q_ASSERT( !identifier.isEmpty() );

        QString prefixedIdentifier = internalID< T >( identifier );
        if( m_resources.contains( prefixedIdentifier ) )
            m_resources.remove( prefixedIdentifier );
    }

    template < typename T >
    void ResourceManager::destroyResource( const QString& identifier )
    {
        static_assert( std::is_base_of< QObject, T >::value, "Object must be a QObject subclass" );
        Q_ASSERT( !identifier.isEmpty() );

        QString prefixedIdentifier = internalID< T >( identifier );
        QObject* resource = m_resources.value( prefixedIdentifier );
        if( resource )
        {
            m_resources.remove( prefixedIdentifier );
            delete resource;
        }
    }

    template < typename T >
    QString ResourceManager::internalID( const QString& id )
    {
        return QString( "%1::%2" ).arg( T::staticMetaObject.className() ).arg( id );
    }
}

#endif // GLUONCORE_MANAGER_H

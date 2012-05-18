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

#include <core/singleton.h>

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
            Backend* backend();

            World* createWorld( const QString& identifier = defaultWorld );
            World* world( const QString& identifier = defaultWorld ) const;
            void destroyWorld( const QString& identifier = defaultWorld );
            World* currentWorld() const;

            void setCurrentWorld( const QString& identifier = defaultWorld );

            void addResource( const QString& identifier, QObject* object );
            QObject* resource( const QString& identifier );
            void removeResource( QObject* resource );

//             template < typename T >
//             T* createResource( const QString& identifier );
//
//             template < typename T >
//             void addResource( const QString& identifier, T* object );
//
//             template < typename T >
//             T* resource( const QString& identifier ) const;
//
//             template < typename T >
//             void destroyResource( const QString& identifier );

            static const QString defaultWorld;
            static const QString defaultRenderTarget;

        private:
            ~Manager();

            class Private;
            const QScopedPointer< Private > d;
    };
}

#endif // GLUONGRAPHICS_MANAGER_H

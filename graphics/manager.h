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

namespace GluonGraphics
{

    class Manager : public GluonCore::Singleton< Manager >
    {
        Q_OBJECT
        GLUON_SINGLETON( Manager )

        public:
            Backend* backend();

            World* createWorld( const QString& identifier = defaultWorldIdentifier );
            World* world( const QString& identifier = defaultWorldIdentifier ) const;
            void destroyWorld( const QString& identifier = defaultWorldIdentifier );

            template < typename T >
            T* createResource( const QString& identifier );

//             template < Texture >
//             Texture* createResource( const QString& identifier );

            template < typename T >
            T* resource( const QString& identifier ) const;

            void destroyResource( const QString& identifier );

            static const QString defaultWorldIdentifier;

        private:
            ~Manager();

            class Private;
            const QScopedPointer< Private > d;
    };

}

#endif // GLUONGRAPHICS_MANAGER_H

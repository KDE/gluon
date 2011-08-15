/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUONGRAPHICS_PARTICLESYSTEM_H
#define GLUONGRAPHICS_PARTICLESYSTEM_H

#include <core/gluonobject.h>
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class ParticleEmitter;
    /**
     *
     */
    class ParticleSystem : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT( ParticleSystem )

        public:
            ParticleSystem( QObject* parent = 0 );
            virtual ~ParticleSystem();

            /**
             *
             */
            ParticleEmitter* createEmitter( const QString& name );
            /**
             *
             */
            bool addEmitter( const QString& name, ParticleEmitter* emitter );
            /**
             *
             */
            ParticleEmitter* emitter( const QString& name );
            /**
             *
             */
            void removeEmitter( const QString& name );
            /**
             *
             */
            void destroyEmitter( const QString& name );
            /**
             *
             */
            void update();

        private:
            class Private;
            const QScopedPointer<Private> d;
    };
}

Q_DECLARE_METATYPE( GluonGraphics::ParticleSystem* )

#endif // GLUONGRAPHICS_PARTICLESYSTEM_H

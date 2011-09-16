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
     * \brief A container class for managing particle emitters.
     *
     * This class manages a set of particle emitters, including
     * updating the emitters when needed and serialising or
     * deserialising them.
     */
    class ParticleSystem : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT( ParticleSystem )

        public:
            Q_INVOKABLE ParticleSystem( QObject* parent = 0 );
            virtual ~ParticleSystem();

            /**
             * Load the contents of this systen from a file.
             *
             * The file should be a GDL file describing a particle
             * system. See GluonCore::GDLHandler for more
             * information about GDL.
             *
             * \param path The path to a file to load the data from.
             *
             * \return True if successful, false otherwise.
             */
            bool load( const QUrl& path );

            /**
             * Write the contents of this system to a file.
             *
             * The system will be serialised to GDL and written
             * to the file passed. The file will be overwritten.
             *
             * \param path The path to save the data to.
             *
             * \return True if successful, false otherwise.
             */
            bool save( const QUrl& path );

            /**
             * Unload the entire particle system from memory.
             *
             * This will destroy all emitters, affectors and
             * other associated items.
             */
            void unload();

            /**
             * Create a new emitter inside this particle system.
             *
             * \param name The name used to reference the emitter.
             * \param type The type of emitter.
             */
            ParticleEmitter* createEmitter( const QString& name, const QString& type );

            /**
             * Add an Emitter to this particle system.
             *
             * \param name The name used to reference the Emitter.
             * \param emitter The emitter to add.
             */
            bool addEmitter( const QString& name, ParticleEmitter* emitter );

            /**
             * Retrieve an emitter from this particle system.
             *
             * \param name The name of the emitter to retrieve.
             */
            ParticleEmitter* emitter( const QString& name );

            /**
             * Remove an emitter from this particle system.
             *
             * Note that this will not delete the emitter, for that
             * use destroyEmitter().
             *
             * \param name The name of the emitter to remove.
             */
            void removeEmitter( const QString& name );

            /**
             * Remove and delete an emitter from this particle system.
             *
             * \param name The name of the emitter to destroy.
             */
            void destroyEmitter( const QString& name );

            /**
             * Update the particle system and all the emitters
             * contained within.
             *
             * \param time The amount of time that has elapsed since
             * the last update, in milliseconds.
             */
            void update( int time );

        private:
            class Private;
            const QScopedPointer<Private> d;
    };
}

Q_DECLARE_METATYPE( GluonGraphics::ParticleSystem* )

#endif // GLUONGRAPHICS_PARTICLESYSTEM_H

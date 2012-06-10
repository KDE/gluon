/*****************************************************************************
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

#ifndef GLUONGRAPHICS_SHADER_H
#define GLUONGRAPHICS_SHADER_H

#include <QList>

class QVariant;
namespace GluonGraphics
{

    class Texture;
    /**
     * \brief Abstract base class for an encapsulated GPU shader program.
     *
     */
    class Shader
    {
        public:
            /**
             * \todo Implement support for Geometry, Hull and Domain shaders.
             */
            enum SourceType {
                VertexProgramSource,
                FragmentProgramSource,
                //GeometryProgramSource,
                //DomainProgramSource,
                //HullProgramSource,
            };

            Shader();
            virtual ~Shader();

            virtual QString source( SourceType type ) const;
            virtual void setSource( SourceType type, const QString& source );

            virtual bool build() = 0;
            virtual bool bind() = 0;
            virtual void release() = 0;

            virtual void setProperty( const QString& name, const QVariant& value ) = 0;
            virtual void setProperty( const QString& name, Texture* texture, int textureID = 0 ) = 0;
            virtual QList<int> attributes() = 0;

            QString error() const;

        protected:
            void setError( const QString& error );

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONGRAPHICS_SHADER_H

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

#include <QtCore/QHash>
#include <QtCore/QStringList>

#include "gluon_graphics_export.h"

class QVariant;
namespace GluonGraphics
{

    class Texture;
    /**
     * \brief Abstract base class for an encapsulated GPU shader program.
     *
     */
    class GLUON_GRAPHICS_EXPORT Shader
    {
        public:
            /**
             * \todo Implement support for Geometry, Hull and Domain shaders.
             */
            enum SourceType
            {
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

            virtual QHash< QString, QVariant > uniforms() const;
            virtual bool hasUniform( const QString& name ) const;
            virtual void setUniform( const QString& name, const QVariant& value );
            virtual void setUniforms( const QHash< QString, QVariant >& properties );

            virtual QHash< QString, int > attributes() const;
            virtual bool hasAttribute( const QString& name ) const;
            virtual int attributeIndex( const QString& name ) const;

            QString error() const;

        protected:
            void setError( const QString& error );
            void setAttributes( const QHash< QString, int >& attribs );
            void setUniformNames( const QStringList& names );

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONGRAPHICS_SHADER_H

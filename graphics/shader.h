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
     * Abstract base class for an encapsulated GPU shader program.
     *
     * This class abstracts a GPU shader program, containing all stages
     * like vertex and fragment shaders. In addition, it provides an interface
     * to set uniform values and retrieve attribute indexes from the shader.
     *
     * Note that the uniform parameters are cached and will be re-applied during
     * a second call to bind(). This is mostly done as a convenience, since many
     * uniform values stay the same during consecutive calls. In addition, it allows
     * assigning uniform values before the shader is bound, which makes it possible
     * to set uniform values separately from the code that uses the shader to render.
     */
    class GLUON_GRAPHICS_EXPORT Shader
    {
        public:
            /**
             * The type of shader source to set.
             *
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

            /**
             * Retrieve the code of a specific shader stage.
             *
             * \param type The source code type, i.e. what stage it is assigned to.
             *
             * \return The source code for the specified stage.
             */
            virtual QString source( SourceType type ) const;
            /**
             * Set the source code to use for a certain shader stage.
             *
             * \param type The source code type.
             * \param source The actual source code.
             */
            virtual void setSource( SourceType type, const QString& source );

            /**
             * Compile and link the provided shader source into a single GPU program.
             */
            virtual bool build() = 0;
            /**
             * Bind the shader so it can be used for rendering.
             *
             * Note that this will cause all cached uniform values to be set.
             */
            virtual bool bind() = 0;
            /**
             * Release the shader so it will no longer be used.
             */
            virtual void release() = 0;

            /**
             * \return A list of all uniforms set on this shader.
             */
            virtual QHash< QString, QVariant > uniforms() const;
            /**
             * \return Is the specified uniform set on this shader?
             */
            virtual bool hasUniform( const QString& name ) const;
            /**
             * Set a uniform to a certain value.
             *
             * Note that specific types of uniforms may not be supported by the backend,
             * like arrays.
             *
             * \param name The name of the uniform to set.
             * \param value The value to set the uniform to.
             */
            virtual void setUniform( const QString& name, const QVariant& value );
            /**
             * Set a set of uniform values.
             *
             * \param properties A hash containing key-value pairs of the uniforms to set.
             */
            virtual void setUniforms( const QHash< QString, QVariant >& properties );

            /**
             * \return A hash of name and index of all attributes supported by this shader.
             */
            virtual QHash< QString, int > attributes() const;
            /**
             * \return Does the shader have the specified attribute?
             */
            virtual bool hasAttribute( const QString& name ) const;
            /**
             * \return The index of a specified attribute.
             */
            virtual int attributeIndex( const QString& name ) const;

            /**
             * \return The error that happened during compiling, or an empty string if there was no errror.
             */
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

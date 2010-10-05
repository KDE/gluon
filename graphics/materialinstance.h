/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_MATERIALINSTANCE_H
#define GLUONGRAPHICS_MATERIALINSTANCE_H

#include <core/gluonobject.h>
#include "gluon_graphics_export.h"

namespace GluonGraphics
{

    class Texture;
    class Material;

    /**
     * \brief Set of values that define the parameters of a Material.
     *
     * The MaterialInstance class enables the rendering of a Material.
     * It defines all the necessary parameters that the material needs
     * to be rendered correctly. It does this by looking at its own
     * dynamic properties during a call to bind() and setting all uniform
     * variables related to those properties.
     */
    class GLUON_GRAPHICS_EXPORT MaterialInstance : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT(MaterialInstance)

        public:
            /**
             * Constructor.
             *
             * Creates an unassigned MaterialInstance. It is recommended
             * to use Material::createInstance instead.
             *
             * \see Material::createInstance
             */
            Q_INVOKABLE explicit MaterialInstance(QObject* parent = 0);

            /**
             * Destructor.
             */
            virtual ~MaterialInstance();

            /**
             * Bind the MaterialInstance for rendering.
             *
             * This will switch the current OpenGL state to use the
             * shader from the Material and set the appropriate
             * parameters on this shader.
             */
            virtual void bind();

            /**
             * Release the MaterialInstance from rendering.
             */
            virtual void release();

            /**
             * Retrieve the material used by this material instance.
             *
             * \return The material this material instance uses.
             */
            Material * material();

            /**
             * Set the material this material instance uses.
             *
             * \param material The material to use.
             */
            void setMaterial(Material * material);

            /**
             * Retrieve the location of a uniform variable from the underlying
             * shader program.
             *
             * \param name The name of the uniform to retrieve the location for,
             *
             * \return The location of the uniform variable.
             */
            int uniformLocation(const QString& name);

            /**
             * Retrieve the location of a uniform variable from the underlying
             * shader program.
             *
             * \param name The name of the uniform to retrieve the location for,
             *
             * \return The location of the uniform variable.
             */
            int attributeLocation(const QString& attrib);

            /**
             * Sets the modelViewProj uniform variable.
             * The modelViewProj uniform contains the model-view-projection
             * matrix, which is the matrix determining where to render the
             * current model. This specific uniform should always be available.
             *
             * \note It is assumed that the material is bound when this method
             * is called.
             *
             * \param mvp The model-view-projection matrix to set the uniform to.
             */
            void setModelViewProjectionMatrix( QMatrix4x4 mvp );

            /**
             * Set local properties according to the information supplied by
             * the material.
             */
            void setPropertiesFromMaterial();

        protected:
            /**
             * Set the actual uniform variable.
             * This method determines the type of the variant passed in
             * as value and then proceeds to set the uniform to this
             * value.
             *
             * \note It is assumed that the material is bound when this
             * method is called.
             *
             * \param name The name of the uniform to set the value of.
             * \param value The value to set the uniform to.
             */
            void setGLUniform(const QString& name, const QVariant& value);

            /**
             * Bind a texture to a uniform variable.
             *
             * \param name The name of the uniform. It is expected to be in the
             * form "textureX" where X is the number of the texture unit to use.
             * \param tex The texture to bind.
             */
            void bindTexture( const QString& name, GluonGraphics::Texture* tex);

        private:
            class MaterialInstancePrivate;
            MaterialInstancePrivate * const d;
    };

}

Q_DECLARE_METATYPE(GluonGraphics::MaterialInstance);
Q_DECLARE_METATYPE(GluonGraphics::MaterialInstance*);

#endif // GLUONGRAPHICS_MATERIALINSTANCE_H

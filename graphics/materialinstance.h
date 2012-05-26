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

#include "gluon_graphics_export.h"

#include <core/gluonobject.h>
#include <core/referencecounter.h>

namespace GluonGraphics
{

    class Texture;
    class Material;
    class Camera;

    /**
     * \brief Set of values that define the parameters of a Material.
     *
     * The MaterialInstance class enables the rendering of a Material.
     * It defines all the necessary parameters that the material needs
     * to be rendered correctly. It does this by looking at its own
     * dynamic properties during a call to bind() and setting all uniform
     * variables related to those properties.
     *
     * The MaterialInstance gets the currently active camera from the
     * scene and uses that to set the view and projections matrices for the
     * vertex shader. The model matrix is set from within the Item class. You
     * will need to calculate the model-view-projection matrix from those
     * values in the vertex shader.
     */
    class GLUON_GRAPHICS_EXPORT MaterialInstance : public GluonCore::GluonObject, public GluonCore::ReferenceCounter
    {
            Q_OBJECT
            GLUON_OBJECT( GluonGraphics::MaterialInstance )

            Q_CLASSINFO( "org.gluon.icon", "text-mathml" )

        public:
            /**
             * Constructor.
             *
             * Creates an unassigned MaterialInstance. It is recommended
             * to use Material::createInstance instead.
             *
             * \see Material::createInstance
             */
            Q_INVOKABLE explicit MaterialInstance( QObject* parent = 0 );

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
             *
             * @return True if the bind was successful, false if not.
             */
            virtual bool bind();

            /**
             * Release the MaterialInstance from rendering.
             */
            virtual void release();

            /**
             * Retrieve the material used by this material instance.
             *
             * \return The material this material instance uses.
             */
            Material* material();

            /**
             * Set the material this material instance uses.
             *
             * \param material The material to use.
             */
            void setMaterial( Material* material );

            /**
             * Bind a texture to a uniform variable.
             *
             * \param name The name of the uniform.It is expected to be in the
             * form "textureX" where X is the number of the texture unit to use.
             * \param tex The texture to bind.
             */
            void bindTexture( const QString& name, GluonGraphics::Texture* tex );

            /**
             * Bind an OpenGL texture id to a uniform variable.
             *
             * \param name The name of the uniform to bind to. It is expected to
             * be in the form "textureX" where X is the number of the texture
             * unit to use.
             * \param tex The id of the texture.
             */
            void bindTexture( const QString& name, int tex );

            /**
             * Retrieve the location of a uniform variable from the underlying
             * shader program.
             *
             * \param name The name of the uniform to retrieve the location for,
             *
             * \return The location of the uniform variable.
             */
            int uniformLocation( const QString& name );

            /**
             * Retrieve the location of a uniform variable from the underlying
             * shader program.
             *
             * \param name The name of the uniform to retrieve the location for,
             *
             * \return The location of the uniform variable.
             */
            int attributeLocation( const QString& attrib );

            /**
             * Set local properties according to the information supplied by
             * the material.
             */
            void setPropertiesFromMaterial();

            /**
             * Set whether to use custom View and Projection matrices instead of
             * getting them from the currently active camera.
             */
            void setUseCustomViewProjMatrices( bool useCustom );

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
            void setGLUniform( const QString& name, const QVariant& value );

        private:
            class Private;
            Private* const d;

            Q_PRIVATE_SLOT( d, void setActiveCamera( Camera* camera ) );

    };

}

Q_DECLARE_METATYPE( GluonGraphics::MaterialInstance* )

#endif // GLUONGRAPHICS_MATERIALINSTANCE_H

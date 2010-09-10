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
    class Material;

    /**
     * \brief Set of values that define the parameters of a Material.
     *
     * The MaterialInstance class enables the rendering of a Material.
     * It defines all the necessary parameters that the material needs
     * to be rendered correctly. These parameters should be defined as
     * dynamic properties.
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
            explicit MaterialInstance(QObject* parent = 0);
            explicit MaterialInstance(Material * instanceOf);

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
             * \return The material this MaterialInstance is an instance of.
             */
            Material * instanceOf();

            int parameterLocation(const QString& param);
            int attributeLocation(const QString& attrib);

            void setParameter(const QString& param, const QVariant& value);
            void setModelViewProjectionMatrix( QMatrix4x4 mvp );

        private:
            class MaterialInstancePrivate;
            MaterialInstancePrivate * const d;
    };

}

Q_DECLARE_METATYPE(GluonGraphics::MaterialInstance);
Q_DECLARE_METATYPE(GluonGraphics::MaterialInstance*);

#endif // GLUONGRAPHICS_MATERIALINSTANCE_H

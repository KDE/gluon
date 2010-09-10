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

#ifndef GLUONGRAPHICS_MATERIAL_H
#define GLUONGRAPHICS_MATERIAL_H

#include "gluon_graphics_export.h"
#include <core/gluonobject.h>

namespace GluonGraphics
{
    class MaterialInstance;
    class Technique;

    /**
    * \brief Collection of techniques which describe how to render a surface.
    *
    * A material is an object containing a set of techniques.
    * Each technique describes a single way to render the surface
    * of an object.
    *
    * Materials cannot be directly rendered. Instead, you will need a
    * MaterialInstance of the Material to render it. This is because
    * the Material class is more like a code-generation tool. It
    * generates shader code at runtime and compiles it into an OpenGL
    * shader. The MaterialInstance then defines the values for the
    * shader's uniform and attribute values.
    *
    * MaterialInstances also control which technique is used to render
    * the material. In addition, each material has a default technqiue
    * which will be used if no override has been given.
    *
    * \see MaterialInstance
    */
    class GLUON_GRAPHICS_EXPORT Material : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT(Material)

        public:
            /**
             * Constructor.
             *
             * Constructs an empty material.
             */
            Material(QObject* parent = 0);
            /**
             * Destructor.
             */
            virtual ~Material();

            /**
             * Build the shader.
             *
             * This processes the selected technique and generates
             * the shader code. Once done, it then compiles the
             * generated GLSL shader. If the shader compiles
             * correctly, the appropriate parameters will be retrieved
             * and can then be set.
             *
             * \param technique The name of the technique to use
             * for the build process. Passing an empty string means
             * it will use the default technique.
             */
            void build(const QString& name = QString());

            /**
             * Retrieve a technique by name.
             *
             * \param name The name of the technique to retrieve.
             *
             * \return The technique with the name "name" or
             * 0 if it was not found. Passing an empty string
             * will return the default technique.
             */
            Technique* technique(const QString& name = QString()) const;

            /**
             * Add a technique to the material.
             *
             * Note that this will reparent the technique
             * to this material.
             *
             * \param technique The technique to add.
             */
            void addTechnique(Technique* technique);

            /**
             * Remove a technique from the material.
             *
             * The named technique will not be deleted
             * but its parent will be set to 0.
             *
             * \param name The name of the technique to remove.
             */
            void removeTechnique(const QString& name);

            /**
             * Set the default technique.
             *
             * \param name The name of the technique to use as
             * default.
             *
             * \see defaultTechnique
             */
            void setDefaultTechnique(const QString& name);

            /**
             * Create a MaterialInstance object for this material.
             *
             * This will create a MaterialInstance object with all
             * the parameters of this material set as properties on
             * the object.
             *
             * \return The MaterialInstance object just created.
             *
             * \see MaterialInstance
             */
            MaterialInstance * createInstance();

            /**
             * Retrieve the internal OpenGL Program identifier.
             *
             * \return The OpenGL identifier for the program or
             * 0 if build was not yet called.
             */
            uint glProgram();

        private:
            class MaterialPrivate;
            MaterialPrivate * const d;
    };
}

Q_DECLARE_METATYPE(GluonGraphics::Material);
Q_DECLARE_METATYPE(GluonGraphics::Material*);

#endif // GLUONGRAPHICS_MATERIAL_H

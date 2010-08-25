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
    * generates shader code at runtime, which the material instance
    * uses to create a shader program from and set all the needed
    * parameters for.
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
             * This builds the shader code for this material.
             *
             * \param technique The name of the technique to use
             * for the build process.
             *
             * \return A QString-QString hash containing shader
             * code identified by the phase they are meant for.
             * E.g.: "vertex" for vertex shaders and "fragment" for
             * fragment shaders.
             */
            QHash<QString, QString> build(const QString& name);

            /**
             * Retrieve a technique by name.
             *
             * \param name The name of the technique to retrieve.
             *
             * \return The technique with the name "name" or
             * 0 if it was not found.
             */
            Technique* technique(const QString& name) const;

            /**
             * Retrieve the default technique.
             *
             * The default technique is the technique the
             * material will use when no active technique
             * has been set.
             *
             * \return The default technique.
             */
            Technique* defaultTechnique() const;

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

        private:
            class MaterialPrivate;
            MaterialPrivate * const d;
    };
}

Q_DECLARE_METATYPE(GluonGraphics::Material);
Q_DECLARE_METATYPE(GluonGraphics::Material*);

#endif // GLUONGRAPHICS_MATERIAL_H

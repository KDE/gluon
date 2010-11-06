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

#ifndef GLUONGRAPHICS_TECHNIQUE_H
#define GLUONGRAPHICS_TECHNIQUE_H

#include "gluon_graphics_export.h"
#include <core/gluonobject.h>

namespace GluonGraphics
{
    class Material;

    /**
     * \brief A single way of rendering a surface.
     *
     * The technique class describes a single way of
     * rendering a surface. Each technique contains a tree
     * of MaterialElement items which correspond to single
     * elements of a shader. The technique class bundles
     * these elements and builds a shader out of this tree.
     *
     * \ingroup Gluon Graphics
     */
    class GLUON_GRAPHICS_EXPORT Technique : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT( Technique )

        public:
            Technique( QObject* parent = 0 );
            virtual ~Technique();

            QHash<QString, QString> build();

            Material* material();

        private:
            class TechniquePrivate;
            TechniquePrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonGraphics::Technique );
Q_DECLARE_METATYPE( GluonGraphics::Technique* );

#endif // GLUONGRAPHICS_TECHNIQUE_H

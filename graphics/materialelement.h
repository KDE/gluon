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

#ifndef GLUONGRAPHICS_MATERIALELEMENT_H
#define GLUONGRAPHICS_MATERIALELEMENT_H

#include <core/gluonobject.h>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT MaterialElement : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT(MaterialElement)
        
        public:
            MaterialElement(QObject* parent = 0);
            virtual ~MaterialElement();

        private:
            class MaterialElementPrivate;
            MaterialElementPrivate * const d;
    };

}

Q_DECLARE_METATYPE(GluonGraphics::MaterialElement)
Q_DECLARE_METATYPE(GluonGraphics::MaterialElement*)

#endif // GLUONGRAPHICS_MATERIALELEMENT_H

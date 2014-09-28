/******************************************************************************
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

#ifndef GLUONGRAPHICS_DEFAULTS_H
#define GLUONGRAPHICS_DEFAULTS_H

#include <QtCore/QHash>
#include <QtCore/QVariant>

#include <core/singleton.h>
#include <core/debughelper.h>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    /**
     */
    class GLUON_GRAPHICS_EXPORT Defaults
    {

        public:
            /**
             * Names for certain default objects that should always be available.
             */
            static const QString World;
            static const QString RenderTarget;
            static const QString Material;
            static const QString MaterialInstance;
            static const QString SpriteMesh;
            static const QString Texture;

            /**
             * Initialize the default objects.
             */
            static void initialize();
    };
}

#endif // GLUONGRAPHICS_DEFAULTS_H

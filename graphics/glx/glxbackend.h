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

#ifndef GLUONGRAPHICS_GLXBACKEND_H
#define GLUONGRAPHICS_GLXBACKEND_H

#include <QtCore/QScopedPointer>
#include <graphics/backend.h>

namespace GluonGraphics
{
    class GLXContext;

    class GLXBackend : public GluonGraphics::Backend
    {
        public:
            GLXBackend();
            virtual ~GLXBackend();

            GLXContext* context();
            virtual Buffer* createBuffer();
            virtual TextureData* createTextureData();
            virtual Shader* createShader();
            virtual OutputSurface* createOutputSurface();

        private:
            class Private;
            const QScopedPointer< Private > d;
    };

}

#endif // GLUONGRAPHICS_GLXBACKEND_H

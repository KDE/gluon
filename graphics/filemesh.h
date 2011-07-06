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

#ifndef GLUONGRAPHICS_FILEMESH_H
#define GLUONGRAPHICS_FILEMESH_H

#include "mesh.h"

/**
 * \brief Loads a Mesh from a file.
 *
 * This class loads a mesh from a file, by using the AssetImporter
 * library for loading.
 *
 */
namespace GluonGraphics
{

    class FileMesh : public Mesh
    {
        Q_OBJECT
        public:
            FileMesh( QObject* parent = 0 );
            virtual ~FileMesh();
            virtual void load( const QString& filename );
    };

}

#endif // GLUONGRAPHICS_FILEMESH_H

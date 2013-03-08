/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

namespace GluonGraphics
{
    /**
    * \brief A mesh that is loaded from a file.
    *
    * This class loads a mesh from a file, by using the AssetImporter
    * library for loading.
    *
    */
    class FileMesh : public Mesh
    {
            Q_OBJECT
        public:
            /**
             * Constructor.
             *
             * \param file The file to load the data from.
             */
            explicit FileMesh( const QString& file, QObject* parent = 0 );
            virtual ~FileMesh();

            QString file() const;

            virtual void initialize();

        private:
            class Private;
            Private * const d;
    };

}

#endif // GLUONGRAPHICS_FILEMESH_H

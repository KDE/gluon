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

#include "meshdata.h"

using namespace GluonGraphics;

class MeshData::Private
{
    public:
        Private() : type( TriangleType ), count( 0 ) { }

        PrimitiveType type;
        int count;
};

MeshData::MeshData() : d( new Private )
{

}

MeshData::~MeshData()
{

}

MeshData::PrimitiveType MeshData::primitiveType() const
{
    return d->type;
}

void MeshData::setPrimitiveType( MeshData::PrimitiveType type )
{
    d->type = type;
}

int MeshData::primitiveCount() const
{
    return d->count;
}

void MeshData::setPrimitiveCount( int count )
{
    d->count = count;
}

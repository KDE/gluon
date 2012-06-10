/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#include "spritemesh.h"

#include <QVector>

#include "meshdata.h"
#include "manager.h"
#include "backend.h"
#include "shader.h"

using namespace GluonGraphics;

class SpriteMesh::Private
{
    public:
        Private() : meshData( 0 ) { }

        MeshData* meshData;
};

SpriteMesh::SpriteMesh( QObject* parent )
    : Mesh( parent ), d( new Private )
{

}

SpriteMesh::~SpriteMesh()
{

}

void SpriteMesh::initialize()
{
    d->meshData = Manager::instance()->backend()->createMeshData();
    d->meshData->setPrimitiveType( GluonGraphics::MeshData::TriangleType );
    d->meshData->setPrimitiveCount( 6, 80, 24 );

    QVector< float > vertices;
    vertices << -0.5f << -0.5f << 0.f;
    vertices << -0.5f <<  0.5f << 0.f;
    vertices <<  0.5f <<  0.5f << 0.f;
    vertices <<  0.5f << -0.5f << 0.f;
    d->meshData->setAttribute( "vertex", QVariant::Vector3D, vertices );

    QVector< float > uvs;
    uvs << 0.f << 0.f;
    uvs << 0.f << 1.f;
    uvs << 1.f << 1.f;
    uvs << 1.f << 0.f;
    d->meshData->setAttribute( "uv0", QVariant::Vector2D, uvs );

    d->meshData->setIndices( QVector< uint >() << 0 << 1 << 2 << 0 << 2 << 3 );
}

bool SpriteMesh::isInitialized() const
{
    return d->meshData != 0;
}

void SpriteMesh::render( Shader* shader )
{
    if( d->meshData )
    {
        d->meshData->render( shader );
    }
    else
    {
        qWarning( "Warning: Attempting to render an uninitialised SpriteMesh!" );
    }
}

#include "spritemesh.moc"

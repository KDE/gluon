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
#include "vertexattribute.h"

using namespace GluonGraphics;

SpriteMesh::SpriteMesh( QObject* parent )
    : Mesh( parent )
{

}

SpriteMesh::~SpriteMesh()
{

}

void SpriteMesh::initialize()
{
//     VertexBuffer* buffer = vertexBuffer();
//
//     VertexAttribute vertices( "vertex", 3 );
//     vertices << -1.f << -1.f << 0.f;
//     vertices << -1.f <<  1.f << 0.f;
//     vertices <<  1.f <<  1.f << 0.f;
//     vertices <<  1.f << -1.f << 0.f;
//     buffer->addAttribute( vertices );
//
//     VertexAttribute colors( "color", 4 );
//     colors << 1.f << 1.f << 1.f << 1.f;
//     colors << 1.f << 1.f << 1.f << 1.f;
//     colors << 1.f << 1.f << 1.f << 1.f;
//     colors << 1.f << 1.f << 1.f << 1.f;
//     buffer->addAttribute( colors );
//
//     VertexAttribute uvs( "uv0", 2 );
//     uvs << 0.f << 0.f;
//     uvs << 0.f << 1.f;
//     uvs << 1.f << 1.f;
//     uvs << 1.f << 0.f;
//     buffer->addAttribute( uvs );
//
//     QVector<uint> indices;
//     indices << 0 << 1 << 2
//             << 0 << 2 << 3;
//
//     buffer->setIndices( indices );
//     buffer->initialize();
}

void SpriteMesh::render( Shader* shader )
{

}

#include "spritemesh.moc"

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

#include "filemesh.h"

#include <QVector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "core/debughelper.h"
#include "manager.h"
#include "backend.h"

using namespace GluonGraphics;

class FileMesh::Private
{
    public:
        QString file;
};

FileMesh::FileMesh( const QString& file, QObject* parent )
    : Mesh( parent ), d( new Private )
{
    d->file = file;
}

FileMesh::~FileMesh()
{
    delete d;
}

QString FileMesh::file() const
{
    return d->file;
}

void FileMesh::initialize()
{
    Assimp::Importer imp;
    const aiScene* scene = imp.ReadFile( d->file.toUtf8(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes );

    if( !scene || scene->mNumMeshes == 0 )
    {
        DEBUG_BLOCK
        DEBUG_TEXT2( "Unable to load file mesh: %1", d->file );
        return;
    }

    MeshData* data = Manager::instance()->backend()->createMeshData();
    data->setPrimitiveType( MeshData::TrianglePrimitive );

//    int count = 0;
//     for( uint m = 0; m < scene->mNumMeshes; ++m )
//     {
    aiMesh* mesh = scene->mMeshes[ 0 ];

    data->setPrimitiveCount( mesh->mNumFaces * 3 );

    QVector< float > vertices;
    for( uint i = 0; i < mesh->mNumVertices; ++i )
    {
        aiVector3D vertex = mesh->mVertices[i];
        vertices << vertex.x << vertex.y << vertex.z;
    }
    data->setAttribute( "vertex", MeshData::Vector3fAttribute, vertices );

    QVector<uint> indices;
    for( uint i = 0; i < mesh->mNumFaces; ++i )
    {
        aiFace face = mesh->mFaces[i];
        for( uint j = 0; j < face.mNumIndices; ++j )
        {
            indices << face.mIndices[j];
        }
    }
    data->setIndices( indices );

    uint uvCount = mesh->GetNumUVChannels();
    for( uint t = 0; t < uvCount; ++t )
    {
        aiVector3D* uvChannel = mesh->mTextureCoords[ t ];
        uint numComponents = mesh->mNumUVComponents[ t ];
        MeshData::AttributeType uvType = numComponents == 1 ? MeshData::FloatAttribute : numComponents == 2 ? MeshData::Vector2fAttribute : MeshData::Vector3fAttribute;

        QVector< float > uvs;
        for( uint i = 0; i < mesh->mNumVertices; ++i )
        {
            aiVector3D uv = uvChannel[i];

            uvs << uv.x;
            if(numComponents > 1)
                uvs << uv.y;

            if(numComponents > 2)
                uvs << uv.z;
        }
        data->setAttribute( QString("uv%1").arg( t ), uvType, uvs );
    }

    if( mesh->HasVertexColors(0) )
    {
        aiColor4D* colorChannel = mesh->mColors[0];
        QVector< float > colors;
        for( uint i = 0; i < mesh->mNumVertices; ++i )
        {
            aiColor4D color = colorChannel[i];
            colors << color.r << color.g << color.b << color.a;
        }
        data->setAttribute( "color", MeshData::Vector4fAttribute, colors );
    }

//     if( mesh->HasNormals() )
//     {
//         QVector< float > normals;
//         for( uint i = 0; i < mesh->mNumVertices; ++i )
//         {
//             aiVector3D normal = mesh->mNormals[i];
//             normals << normal.x << normal.y << normal.z;
//         }
//         data->setAttribute( "normal", QVariant::Vector3D, normals );
//     }
//     }

//    data->setPrimitiveCount( count );

    setMeshData( data );
}

#include "filemesh.moc"

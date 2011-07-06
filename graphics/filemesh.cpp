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

#include "filemesh.h"

#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiMesh.h>
#include <assimp/aiPostProcess.h>

#include "core/debughelper.h"

#include "vertexattribute.h"

using namespace GluonGraphics;

FileMesh::FileMesh( QObject* parent )
    : Mesh( parent )
{

}

FileMesh::~FileMesh()
{

}

void FileMesh::load( const QString& filename )
{
    Assimp::Importer imp;
    const aiScene* scene = imp.ReadFile(filename.toUtf8(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType );

    if(!scene)
    {
        return;
    }

    VertexBuffer *buffer = vertexBuffer();
    for(uint m = 0; m < scene->mNumMeshes; ++m)
    {
        aiMesh* mesh = scene->mMeshes[m];

        VertexAttribute vertices("vertex", 3);
        for( uint i = 0; i < mesh->mNumVertices; ++i )
        {
            aiVector3D vertex = mesh->mVertices[i];
            vertices << vertex.x << vertex.y << vertex.z;
        }
        buffer->addAttribute(vertices);

        QVector<uint> indices;
        for( uint i = 0; i < mesh->mNumFaces; ++i )
        {
            aiFace face = mesh->mFaces[i];
            for( uint j = 0; j < face.mNumIndices; ++j )
            {
                indices << face.mIndices[j];
            }
        }
        buffer->setIndices(indices);

        uint uvCount = mesh->GetNumUVChannels();
        for( uint t = 0; t < uvCount; ++t )
        {
            aiVector3D* uvChannel = mesh->mTextureCoords[t];
            uint numComponents = mesh->mNumUVComponents[t];
            VertexAttribute uvs(QString("uv%1").arg(t), numComponents);
            for( uint i = 0; i < mesh->mNumVertices; ++i )
            {
                aiVector3D uv = uvChannel[i];

                uvs << uv.x;
                if(numComponents > 1)
                    uvs << uv.y;

                if(numComponents > 2)
                    uvs << uv.z;
            }
            buffer->addAttribute(uvs);
        }

        if( mesh->HasVertexColors(0) )
        {
            aiColor4D* colorChannel = mesh->mColors[0];
            VertexAttribute colors("color", 4);
            for( uint i = 0; i < mesh->mNumVertices; ++i )
            {
                aiColor4D color = colorChannel[i];
                colors << color.r << color.g << color.b << color.a;
            }
            buffer->addAttribute(colors);
        }

        if( mesh->HasNormals() )
        {
            VertexAttribute normals("normal", 3);
            for( uint i = 0; i < mesh->mNumVertices; ++i )
            {
                aiVector3D normal = mesh->mNormals[i];
                normals << normal.x << normal.y << normal.z;
            }
            buffer->addAttribute(normals);
        }
    }

    buffer->initialize();
}

#include "filemesh.moc"

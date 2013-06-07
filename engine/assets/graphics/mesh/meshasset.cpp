/******************************************************************************
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

#include "meshasset.h"

#include <graphics/engine.h>
#include <graphics/filemesh.h>

REGISTER_OBJECTTYPE( GluonEngine, MeshAsset )

using namespace GluonEngine;

class MeshAsset::Private
{
    public:
        Private() : mesh(0) {}
        ~Private() {}

        GluonGraphics::FileMesh* mesh;
};

MeshAsset::MeshAsset( QObject* parent )
    : Asset( parent ), d( new Private )
{
}

MeshAsset::~MeshAsset()
{
    delete d;
}

const QStringList MeshAsset::supportedMimeTypes() const
{
    QStringList supportedTypes;
    supportedTypes << "model/vnd.collada+xml";
    supportedTypes << "application/xml";
    supportedTypes << "application/x-blender";
    supportedTypes << "image/x-3ds";
    return supportedTypes;
}

void MeshAsset::load()
{
    if( !file().isEmpty() )
    {
        if( !d->mesh )
        {
            GluonGraphics::Engine::instance()->removeMesh( name() );
            delete d->mesh;
        }

        d->mesh = new GluonGraphics::FileMesh( absolutePath().toLocalFile(), this);
        GluonGraphics::Engine::instance()->addMesh( name(), d->mesh );
        d->mesh->initialize();

        if( d->mesh->isInitialized() )
        {
            mimeData()->setText( name() );
            setLoaded( true );
            return;
        }
    }

    debug( "Error loading mesh: %1", name() );
}

void MeshAsset::setName( const QString& newName )
{
    GluonGraphics::Engine::instance()->removeMesh( name() );
    if( d->mesh )
        GluonGraphics::Engine::instance()->addMesh( newName, d->mesh );
    GluonEngine::Asset::setName( newName );
}

Q_EXPORT_PLUGIN2( gluon_asset_mesh, GluonEngine::MeshAsset )

 

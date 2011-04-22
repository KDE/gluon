/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "soundasset.h"

#include <audio/engine.h>

#include <QtCore/QMimeData>

REGISTER_OBJECTTYPE( GluonEngine, SoundAsset )

using namespace GluonEngine;

SoundAsset::SoundAsset( QObject* parent )
    : Asset( parent )
{
}

SoundAsset::~SoundAsset()
{
}

const QStringList SoundAsset::supportedMimeTypes() const
{
    QStringList list;
    list.append( "audio/x-wav" );
    list.append( "audio/x-vorbis+ogg" );
    list.append( "application/x-ogg" );
    return list;
}

void SoundAsset::load()
{
    mimeData()->setText( absolutePath() );
    setLoaded( true );
}

Q_EXPORT_PLUGIN2( gluon_asset_sound, GluonEngine::SoundAsset )

#include "soundasset.moc"

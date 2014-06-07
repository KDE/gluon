/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#include "achievementsasset.h"

#include <core/gdlserializer.h>
#include <engine/achievement.h>
#include <engine/assetaction.h>

REGISTER_OBJECTTYPE( GluonEngine, AchievementsAsset )

using namespace GluonEngine;

class AchievementsAsset::AchievementsAssetPrivate
{
    public:
        AchievementsAssetPrivate() : fileExtension( "gluonachievements" ) {}
        ~AchievementsAssetPrivate() {}

        const QString fileExtension;
};

AchievementsAsset::AchievementsAsset(QObject* parent)
    : Asset( parent )
    , d( new AchievementsAssetPrivate )
{
    savableDirty = true;
}

AchievementsAsset::~AchievementsAsset()
{
    delete d;
}

void AchievementsAsset::writeContents(QIODevice* device)
{
    GluonCore::GluonObjectList objects;
    for( QObject* object : children() )
    {
        GluonCore::GluonObject* gobj = qobject_cast< GluonCore::GluonObject* >( object );
        if( gobj )
            objects.append( gobj );
    }

    GluonCore::GDLSerializer::instance()->write( device, objects );
}

void AchievementsAsset::load()
{
    if( isLoaded() )
        return;

    // As long as we don't unload correctly, make sure we don't load the objects two times
    foreach( QObject* child, children() )
    {
        Achievement* achievement = qobject_cast<Achievement*>(child);
        if( achievement )
            return;
    }

    // Make sure that we don't get into an endless recursion...
    setLoaded( true );

    GluonCore::GluonObjectList list;
    if( !GluonCore::GDLSerializer::instance()->read( absolutePath(), list, gameProject(), this ) )
    {
        setLoaded( false );
        return;
    }

    foreach( GluonCore::GluonObject* gobj, list )
    {
        Achievement* achievement = qobject_cast<Achievement*>( gobj );
        if( achievement )
            achievement->setParent( this );
    }

    GluonEngine::Asset::load();
}

void AchievementsAsset::unload()
{
    if( !isLoaded() )
        return;

    // This is causing a crash when saving & closing creator
//     QObjectList childList( children() );
//     foreach( QObject* object, childList )
//     {
//         Achievement* achievement = qobject_cast<Achievement*>( object );
//         if( achievement )
//             achievement->deleteLater();
//     }

    GluonEngine::Asset::unload();
}

void AchievementsAsset::setFile(const QString& newFile)
{
    GluonEngine::Asset::setFile( newFile );

    if( isLoaded() )
        reload();
}

void AchievementsAsset::createAchievement()
{
    Achievement* newAchievement = new Achievement(this);
    newAchievement->setName( tr("New Achievement") );
    newAchievement->sanitize();
    savableDirty = true;
}

void AchievementsAsset::populateMetaInfo(GluonCore::MetaInfo* info)
{
    info->setDefaultExtension( d->fileExtension );
}

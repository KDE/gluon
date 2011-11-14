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

#include "achievement.h"

#include <core/gdlserializer.h>

#include <QtGui/QAction>

REGISTER_OBJECTTYPE( GluonEngine, AchievementsAsset )

using namespace GluonEngine;

class AchievementsAsset::AchievementsAssetPrivate
{
    public:
        AchievementsAssetPrivate() : fileExtension( "gluonachievements" ) {}
        ~AchievementsAssetPrivate() {}

        QList<QAction*> actions;
        const QString fileExtension;
};

AchievementsAsset::AchievementsAsset(QObject* parent)
    : Asset( parent )
    , d( new AchievementsAssetPrivate )
{
    QAction* newAchievement = new QAction( tr("New Achievement"), 0 );
    connect( newAchievement, SIGNAL(triggered()), this, SLOT(createAchievement()) );
    d->actions.append( newAchievement );
    savableDirty = true;
}

AchievementsAsset::~AchievementsAsset()
{
    qDeleteAll( d->actions );
    delete d;
}

const QStringList AchievementsAsset::supportedMimeTypes() const
{
    QStringList mimeTypes;
    mimeTypes << "application/x-gluon-achievements";
    return mimeTypes;
}

void AchievementsAsset::writeContents(QIODevice* device)
{
    GluonCore::GluonObjectList objects;
    foreach( QObject* object, children() )
    {
        GluonCore::GluonObject* gobj = qobject_cast< GluonCore::GluonObject* >( object );
        if( gobj )
            objects.append( gobj );
    }

    GluonCore::GDLSerializer::instance()->write( device, objects );
}

const QList< AssetTemplate* > AchievementsAsset::templates()
{
    QList< AssetTemplate* > templates;
    templates.append( new AssetTemplate( tr("Achievements Asset"), "achievements_template." + d->fileExtension, "achievements", this ) );
    return templates;
}

QList< QAction* > AchievementsAsset::actions()
{
    return d->actions;
}

void AchievementsAsset::setFile(const QUrl& newFile)
{
    /* This function will extract the achievement instances
     * from the file only the first time. If it would read
     * the file every time this function is called, it would
     * add the same instance multiple times. If I try do delete
     * all achievements before, gluon creator crashes.
     */
    GluonEngine::Asset::setFile( newFile );

    foreach( QObject* object, children() )
    {
        Achievement* achievement = qobject_cast<Achievement*>( object );
        if( achievement )
            return;
    }

    GluonCore::GluonObjectList list;
    if( !GluonCore::GDLSerializer::instance()->read( file(), list ) )
        return;

    foreach( GluonCore::GluonObject* gobj, list )
    {
        Achievement* achievement = qobject_cast<Achievement*>( gobj );
        if( achievement )
            achievement->setParent( this );
    }
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

Q_EXPORT_PLUGIN2( gluon_asset_achievements, GluonEngine::AchievementsAsset )

#include "achievementsasset.moc"

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

#include <core/gdlhandler.h>

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

QString AchievementsAsset::contentsToGDL()
{
    /* Due to a bug in GDL, it can't handle more than one top level
     * item. This workaround creates a temporary object which takes
     * the achievements as children.
     * TODO: remove as soon as the GDL bug is fixed
     */
    GluonCore::GluonObject object;
    object.setName( "temporaryObjectAchievements" );

    QObjectList childList = children();
    QMutableListIterator<QObject*> i( childList );
    while( i.hasNext() )
    {
        Achievement* achievement = qobject_cast<Achievement*>( i.next() );
        if( achievement )
            achievement->setParent( &object );
    }
    QString result = GluonCore::GDLHandler::instance()->toGDL(&object);

    QObjectList objectChildList = object.children();
    QMutableListIterator<QObject*> j( objectChildList );
    while( j.hasNext() )
    {
        Achievement* achievement = qobject_cast<Achievement*>( j.next() );
        if( achievement )
            achievement->setParent( this );
    }
    return result;
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

    QObjectList childList = children();
    QMutableListIterator<QObject*> i( childList );
    while( i.hasNext() )
    {
        Achievement* achievement = qobject_cast<Achievement*>( i.next() );
        if( achievement )
            return;
    }

    QList<GluonCore::GluonObject*> list = GluonCore::GDLHandler::instance()->parseGDL( file(), 0 );
    if( list.isEmpty() )
        return;

    GluonCore::GluonObject* tmpObj = list.at(0);

    QObjectList tmpObjChildList = tmpObj->children();
    QMutableListIterator<QObject*> j( tmpObjChildList );
    while( j.hasNext() )
    {
        Achievement* achievement = qobject_cast<Achievement*>( j.next() );
        if( achievement )
            achievement->setParent( this );
    }
    delete tmpObj;
}

void AchievementsAsset::createAchievement()
{
    Achievement* newAchievement = new Achievement(this);
    newAchievement->setName( tr("New Achievement") );
    savableDirty = true;
}

void AchievementsAsset::populateMetaInfo(GluonCore::MetaInfo* info)
{
    info->setDefaultExtension( d->fileExtension );
}

Q_EXPORT_PLUGIN2( gluon_asset_achievements, GluonEngine::AchievementsAsset )

#include "achievementsasset.moc"

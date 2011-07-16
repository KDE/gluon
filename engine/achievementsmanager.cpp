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

#include "achievementsmanager.h"

#include <engine/achievement.h>
#include <engine/assets/graphics/texture/textureasset.h>
#include <core/gluonobject.h>
#include <core/directoryprovider.h>
#include <core/gdlhandler.h>

#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

using namespace GluonEngine;

AchievementsManager::AchievementsManager( QObject* parent )
    : QObject( parent )
{
}

AchievementsManager::~AchievementsManager()
{
}

void AchievementsManager::load( const QString& directory )
{
    //cleanup
    foreach( QObject* child, children() )
    {
        child->setParent(0);
        delete child;
    }

    QDir::home().mkpath(directory);
    QList<GluonCore::GluonObject*> objectList = GluonCore::GDLHandler::instance()->parseGDL( directory + "/achievementsCache.gdl" );
    if( objectList.isEmpty() )
        return;

    GluonCore::GluonObject* tmpObject = objectList[0];
    foreach( QObject* object, tmpObject->children() )
    {
        GluonCore::GluonObject* gluonObject = qobject_cast<GluonCore::GluonObject*>(object);
        if( gluonObject )
            gluonObject->setParent(this);
    }
    delete tmpObject;
}

void AchievementsManager::readFromProject( const QList< Achievement* >& achievements )
{
    qDebug() << "Achievement size: " << achievements.count();
    //cleanup
    foreach( QObject* child, children() )
    {
        child->setParent(0);
        delete child;
    }

    //sort
    QList< Achievement* > achieved;
    QList< Achievement* > inProgress;
    QList< Achievement* > locked;
    foreach( Achievement* achievement, achievements )
        if( achievement->achieved() )
            achieved.append(achievement);
        else if( achievement->isHidden() && !achievement->madeProgress() )
            continue;
        else if( achievement->dependencySatisfied() )
            inProgress.append(achievement);
        else
            locked.append(achievement);

    QList< Achievement* > allAchievements = achieved;
    allAchievements.append(inProgress);
    allAchievements.append(locked);

    foreach( Achievement* achievement, allAchievements )
    {
        GluonCore::GluonObject* object = new GluonCore::GluonObject(this);
        object->setProperty( "path", achievement->fullyQualifiedName() );
        object->setProperty( "name", achievement->name() );
        object->setProperty( "description", achievement->property("description") );
        if( achievement->icon() )
            object->setProperty( "icon", achievement->icon()->file().toLocalFile() );
        object->setProperty( "minimumScore", achievement->minimumScore() );
        object->setProperty( "thresholdScore", achievement->thresholdScore() );
        object->setProperty( "currentScore", achievement->currentScore() );
        object->setProperty( "hasDependency", achievement->hasDependency() );
        if( achievement->hasDependency() )
            object->setProperty( "dependency", allAchievements.indexOf( achievement->dependency() ) );
        object->setProperty( "dependencySatisfied", achievement->dependencySatisfied() );
        object->setProperty( "hidden", achievement->isHidden() );
        object->setProperty( "achieved", achievement->achieved() );
    }
}

void AchievementsManager::makeTemplate()
{
    QObjectList childList = children();
    QMutableListIterator<QObject*> i( childList );
    while( i.hasNext() )
    {
        GluonCore::GluonObject* object = qobject_cast<GluonCore::GluonObject*>( i.next() );
        if( object )
        {
            if( object->property( "hidden" ).toBool() )
                delete object;
            object->setProperty( "currentScore", 0 );
            if( object->property( "hasDependency" ).toBool() )
                object->setProperty( "dependencySatisfied", false );
            object->setProperty( "achieved", false );
        }
    }
}

void AchievementsManager::save( const QString& directory )
{
    GluonCore::GluonObject tmpObject;
    foreach( QObject* child, children() )
    {
        GluonCore::GluonObject* object = qobject_cast<GluonCore::GluonObject*>(child);
        if( object )
            object->setParent(&tmpObject);
    }
    QString gdlData = GluonCore::GDLHandler::instance()->toGDL(&tmpObject);
    QDir::home().mkpath(directory);
    QFile file( directory + "/achievementsCache.gdl" );
    if( !file.open(QIODevice::WriteOnly) )
        return;

    QTextStream stream( &file );
    stream << gdlData;
    file.close();

    foreach( QObject* object, tmpObject.children() )
    {
        GluonCore::GluonObject* gluonObject = qobject_cast<GluonCore::GluonObject*>(object);
        if( gluonObject )
            gluonObject->setParent(this);
    }
}

int AchievementsManager::achievementsCount() const
{
    return children().count();
}

QString AchievementsManager::achievementPath(int index) const
{
    return children()[index]->property("path").toString();
}

QString AchievementsManager::achievementName(int index) const
{
    return children()[index]->property("name").toString();
}

QString AchievementsManager::description(int index) const
{
    return children()[index]->property("description").toString();
}

QString AchievementsManager::achievementIcon(int index) const
{
    return children()[index]->property( "icon" ).toString();
}

qlonglong AchievementsManager::minimumScore(int index) const
{
    return children()[index]->property( "minimumScore" ).toLongLong();
}

qlonglong AchievementsManager::thresholdScore(int index) const
{
    return children()[index]->property( "thresholdScore" ).toLongLong();
}

qlonglong AchievementsManager::currentScore(int index) const
{
    return children()[index]->property( "currentScore" ).toLongLong();
}

int AchievementsManager::dependency(int index) const
{
    return children()[index]->property( "dependency" ).toInt();
}

bool AchievementsManager::dependencySatisfied(int index) const
{
    return children()[index]->property( "dependencySatisfied" ).toBool();
}

bool AchievementsManager::hidden(int index) const
{
    return children()[index]->property( "hidden" ).toBool();
}

bool AchievementsManager::achievementAchieved(int index) const
{
    return children()[index]->property("achieved").toBool();
}

bool AchievementsManager::madeProgress(int index) const
{
    QObject* object = children()[index];
    return ( object->property( "currentScore" ).toLongLong() > object->property( "thresholdScore" ).toLongLong() );
}

#include "achievementsmanager.moc"

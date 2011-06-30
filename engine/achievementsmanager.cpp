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

    foreach( Achievement* achievement, achievements )
    {
        GluonCore::GluonObject* object = new GluonCore::GluonObject(this);
        object->setProperty( "path", achievement->fullyQualifiedName() );
        object->setProperty( "name", achievement->name() );
        if( achievement->icon() )
            object->setProperty( "icon", achievement->icon()->file().toLocalFile() );
        object->setProperty( "minimumScore", achievement->minimumScore() );
        object->setProperty( "currentScore", achievement->currentScore() );
        object->setProperty( "hasDependency", achievement->hasDependency() );
        object->setProperty( "dependencySatisfied", achievement->dependencySatisfied() );
        object->setProperty( "achieved", achievement->achieved() );
    }
}

void AchievementsManager::makeTemplate()
{
    foreach( QObject* child, children() )
    {
        GluonCore::GluonObject* object = qobject_cast<GluonCore::GluonObject*>(child);
        if( object )
        {
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

QString AchievementsManager::achievementIcon(int index) const
{
    return children()[index]->property( "icon" ).toString();
}

qlonglong AchievementsManager::minimumScore(int index) const
{
    return children()[index]->property( "minimumScore" ).toLongLong();
}

qlonglong AchievementsManager::currentScore(int index) const
{
    return children()[index]->property( "currentScore" ).toLongLong();
}

bool AchievementsManager::dependencySatisfied(int index) const
{
    return children()[index]->property( "dependencySatisfied" ).toBool();
}

bool AchievementsManager::achievementAchieved(int index) const
{
    return children()[index]->property("achieved").toBool();
}

#include "achievementsmanager.moc"

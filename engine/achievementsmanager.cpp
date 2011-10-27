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

#include "achievement.h"
#include "assets/graphics/texture/textureasset.h"

#include <core/gluonobject.h>
#include <core/directoryprovider.h>
#include <core/gdlserializer.h>

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

void AchievementsManager::save( const QString& directory )
{
    GluonCore::GluonObjectList objects;
    foreach( QObject* object, children() )
    {
        GluonCore::GluonObject* gobj = qobject_cast<GluonCore::GluonObject*>( object );
        if( gobj )
            objects.append( gobj );
    }

    if( !GluonCore::GDLSerializer::instance()->write( QUrl( directory + "/achievementscache.gdl" ), objects ) )
        return;
}

void AchievementsManager::load( const QString& directory )
{
    // Delete all children, as they contain old information
    foreach( QObject* child, children() )
    {
        child->setParent(0);
        child->deleteLater();
    }

    QDir::home().mkpath(directory);

    GluonCore::GluonObjectList objectList;
    if( !GluonCore::GDLSerializer::instance()->read( QUrl( directory + "/achievementscache.gdl" ), objectList ) )
        return;

    foreach( GluonCore::GluonObject* object, objectList )
    {
        object->setParent(this);
    }
}

void AchievementsManager::readFromProject( const QList< Achievement* >& achievements )
{
    qDebug() << "Number of Achievements:" << achievements.count();
    // Delete all children, as they contain old information
    foreach( QObject* child, children() )
    {
        child->setParent(0);
        child->deleteLater();
    }

    foreach( Achievement* achievement, achievements )
    {
        GluonCore::GluonObject* object = new GluonCore::GluonObject(this);
        object->setProperty( "path", achievement->fullyQualifiedName() );
        object->setProperty( "name", achievement->name() );
        object->setProperty( "description", achievement->property("description") );
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
    QObjectList childList;
    QMutableListIterator<QObject*> i( childList );
    while( i.hasNext() )
    {
        GluonCore::GluonObject* object = qobject_cast<GluonCore::GluonObject*>( i.next() );
        if( object )
        {
            object->setProperty( "currentScore", 0 );
            if( object->property( "hasDependency" ).toBool() )
                object->setProperty( "dependencySatisfied", false );
            object->setProperty( "achieved", false );
        }
    }
}

int AchievementsManager::achievementsCount() const
{
    return children().count();
}

QString AchievementsManager::achievementPath( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property("path").toString();
}

QString AchievementsManager::achievementName( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property("name").toString();
}

QString AchievementsManager::achievementDescription ( int index) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property( "description" ).toString();
}

QString AchievementsManager::achievementIcon( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property( "icon" ).toString();
}

qlonglong AchievementsManager::minimumScore( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property( "minimumScore" ).toLongLong();
}

qlonglong AchievementsManager::currentScore( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property( "currentScore" ).toLongLong();
}

bool AchievementsManager::dependencySatisfied( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children()[index]->property( "dependencySatisfied" ).toBool();
}

bool AchievementsManager::achievementAchieved( int index ) const
{
    Q_ASSERT_X( index >= 0 && index < achievementsCount(), Q_FUNC_INFO, "index out of range in list of achievements" );
    return children().at(index)->property("achieved").toBool();
}

#include "achievementsmanager.moc"

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
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

#include "tagobject.h"
#include "tagobjectprivate.h"

#include "game.h"
#include "gameobject.h"

#include <QIODevice>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QDebug>

#include <iostream>

using namespace std;

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, TagObject )

TagObject::TagObject()
    : t( new TagObjectPrivate( this ) )
{
}

TagObject::TagObject( QString path )
{
    readFromFile( path );
}
TagObject::~TagObject()
{
    delete t;
}

void TagObject::addTag( GluonEngine::GameObject* object , QString tag )
{
    QSet<QString> set;
    if( t->tags.contains( tag ) )
        set = t->tags[ tag ];
    set.insert( object->name() );
    t->tags.insert( tag, set );
}

void TagObject::addTags( QString objectname, QString tags )
{
    if( tags.isEmpty() || objectname.isEmpty() )
        return;
    clearTags( objectname );
    QStringList taglist = tags.split( QRegExp("\\W+"), QString::SkipEmptyParts );
    foreach( QString tag, taglist )
    {
        QSet<QString> set;
        if( t->tags.contains( tag ) )
            set = t->tags[ tag ];
        set.insert( objectname );
        t->tags.insert( tag, set );
    }
}


void TagObject::addTags( GluonEngine::GameObject* object, QList< QString > tags )
{
    foreach( const QString tag, tags )
        addTag( object, tag );
}

void TagObject::removeTag( GluonEngine::GameObject* object )
{
    QList< QString > list;
    QString objectname = object->name();
    for(QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i)
    {
        if( i.value().contains( objectname ) )
            i.value().remove( objectname );
        if( i.value().isEmpty() )
            list.append( i.key() );
    }
    foreach( QString item, list )
        t->tags.remove( item );
}

QList< QString > TagObject::objects( QString tag )
{
    return t->tags[ tag ].toList();
}

QList< QString > TagObject::objects( GameObject* scene, QString tag )
{
    QList< QString > list = t->tags[ tag ].toList();
    QStringList objectlist = objectsFromScene( scene );
    foreach( QString object, objectlist )
        if( list.contains( baseName( object ) ) )
            list.append( object );
    return list;
}


QList< QString > TagObject::tags( GluonEngine::GameObject* object )
{
    QString objectname = object->name();
    QList< QString> list;
    for(QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i)
        if( i.value().contains( objectname ) )
            list.append( i.key() );
    return list;
}

QString TagObject::tags( QString objectname )
{
    QStringList list;
    for(QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i)
        if( i.value().contains( objectname ) )
            list.append( i.key() );
    if( list.isEmpty() )
    {
        if( objectname.compare( baseName( objectname ) ) == 0 )
            return QString("");
        else
            return tags( baseName( objectname ) );
    }
    return list.join( ", " );
}

void TagObject::printTags()
{
    for(QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i)
        qDebug() << i.key().toUtf8().constData() << ' ' << QStringList( i.value().toList() ).join(" ").toUtf8().constData();
}

bool TagObject::writeToFile()
{
    return writeToFile( t->path );
}

bool TagObject::writeToFile( QString path )
{
    removeClones();
    QString dir = path.section( '/', 0, -2 );
    if( ! QDir( dir ).exists() )
        QDir().mkpath( dir );
    QFile file( path );
    if( !file.open( QIODevice::WriteOnly ) )
        return false;
    QTextStream out( &file );
    for(QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i)
        out << i.key().toUtf8().constData() << ' ' << QStringList( i.value().toList() ).join(" ").toUtf8().constData() << '\n';
    file.close();
    return true;
}


bool TagObject::readFromFile()
{
    return readFromFile( t->path );
}

bool TagObject::readFromFile( QString path )
{
    QFile file( path );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        writeToFile( path );
        return false;
    }
    t->tags.clear();
    QTextStream in( &file );
    QString line = in.readLine();
    while( ! line.isNull() )
    {
        QList< QString > list = line.split(" ");
        QString key = list.first();
        list.pop_front();
        t->tags[ key ] = list.toSet();
        line = in.readLine();
    }
    file.close();
    return true;
}

void TagObject::setPath( QUrl path )
{
    t->path = path.toLocalFile() + QString("/assets/tags/tags.gs");
    readFromFile();
}

void TagObject::clearTags( QString objectname )
{
    QStringList list;
    for(QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i)
        if( i.value().contains( objectname ) )
        {
            i.value().remove( objectname );
            if( i.value().isEmpty() )
                list.append( i.key () );
        }
    foreach( QString key, list )
        t->tags.remove( key );
}

QString TagObject::baseName( QString objectname )
{
    QStringList list = objectname.split( QRegExp("\\W+"), QString::SkipEmptyParts );
    if( !list.isEmpty() )
        return list.first();
}

QStringList TagObject::objectsFromScene( GluonEngine::GameObject* scene )
{
    QStringList list;
    list.append( scene->name() );
    for( int i = 0; i < scene->childCount(); i++ )
        list.append( objectsFromScene( scene->childGameObject( i ) ) );
    return list;
}

void TagObject::removeClones()
{
    for( QHash<QString, QSet<QString> >::iterator i = t->tags.begin(); i != t->tags.end(); ++i )
        foreach( QString object, i.value() )
            if( object.compare( baseName( object ) ) != 0 )
                i.value().remove( object );
}

#include "tagobject.moc"

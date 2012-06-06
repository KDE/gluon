#include "tagobject.h"
#include "game.h"

#include <engine/gameobject.h>

#include <QIODevice>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>

#include <iostream>

using namespace std;

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, TagObject )

TagObject::TagObject()
{
    this->tags.clear();
}

TagObject::TagObject( GluonEngine::TagObject* other )
{
    for(QHash<QString, QSet<QString> >::iterator i = other->tags.begin(); i != other->tags.end(); ++i)
        this->tags[ i.key() ] = i.value();
}

TagObject::TagObject( QString path )
{
    readFromFile( path );
}
TagObject::~TagObject()
{

}

void TagObject::addTag( GluonEngine::GameObject* object , QString tag )
{
    QSet<QString> set;
    if( this->tags.contains( tag ) )
        set = this->tags[ tag ];
    set.insert( object->name() );
    this->tags.insert( tag, set );
    printTags();
}

void TagObject::addTags( GluonEngine::GameObject* object, QList< QString > tags )
{
    foreach( const QString tag, tags )
        addTag( object, tag );
}

void TagObject::removeTag( GluonEngine::GameObject* object )
{
    QString objectname = object->name();
    for(QHash<QString, QSet<QString> >::iterator i = this->tags.begin(); i != this->tags.end(); ++i)
        if( i.value().contains( objectname ) )
            i.value().remove( objectname );
    printTags();
}

QList< QString > TagObject::getObjects( QString tag )
{
    if( this->tags.contains( tag ) )
        return this->tags[ tag ].toList();
}

QList< QString > TagObject::getTags( GluonEngine::GameObject* object )
{
    QString objectname = object->name();
    QList< QString> list;
    for(QHash<QString, QSet<QString> >::iterator i = this->tags.begin(); i != this->tags.end(); ++i)
        if( i.value().contains( objectname ) )
            list.append( i.key() );
    return list;
}

void TagObject::printTags()
{
    for(QHash<QString, QSet<QString> >::iterator i = this->tags.begin(); i != this->tags.end(); ++i)
    {
        cout << i.key().toUtf8().constData() << ": ";
        foreach( QString ob, i.value() )
            cout << ob.toUtf8().constData() << ' ';
    }
    cout << endl;
}

bool TagObject::writeToFile()
{
    QString dir = Game::instance()->gameProject()->dirname().toString() + QString( "/assets/tags/" );
    if( ! QDir( dir ).exists() )
        QDir().mkpath( dir );
    dir += "tags.gs";
    return writeToFile( dir );
}

bool TagObject::writeToFile( QString path )
{
    QFile file( path );
    if( !file.open( QIODevice::WriteOnly ) )
        return false;
    QTextStream out( &file );
    for(QHash<QString, QSet<QString> >::iterator i = this->tags.begin(); i != this->tags.end(); ++i)
        out << i.key().toUtf8().constData() << ' ' << QStringList( i.value().toList() ).join(" ").toUtf8().constData() << '\n';
    file.close();
    return true;
}

bool TagObject::readFromFile()
{
    QString dir = Game::instance()->gameProject()->dirname().toString() + QString( "/assets/tags/" );
    dir += "tags.gs";
    return readFromFile( dir );
}

bool TagObject::readFromFile( QString path )
{
    QFile file( path );
    if( !file.open( QIODevice::ReadOnly ) )
        return false;
    this->tags.clear();
    QTextStream in( &file );
    QString line = in.readLine();
    while( ! line.isNull() )
    {
        QList< QString > list = line.split(" ");
        QString key = list.first();
        list.pop_front();
        this->tags[ key ] = list.toSet();
        line = in.readLine();
    }
    return true;
}
#include "tagobject.moc"

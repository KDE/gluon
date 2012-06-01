#include "tagobject.h"
#include "game.h"

#include <QMetaProperty>
#include <QIODevice>
#include <QFile>
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

TagObject::TagObject( const GluonEngine::TagObject* other )
{
    for(QHash<QString, QSet<QString> >::iterator i = other->tags.begin(); i != other->tags.end(); ++i)
        this->tags.insert( i.key(), i.value() );
}

TagObject::TagObject( QString path )
{
    readFromFile( path );
}
TagObject::~TagObject()
{

}

void TagObject::addTag( GluonCore::GluonObject* object , QString tag )
{
    QSet<QString> set;
    if( this->tags.contains( tag ) )
        set = this->tags[ tag ];
    QMetaProperty property = object->metaObject()->property( 0 );
    set.insert( property.read( object ).toString() );
    this->tags.insert( tag, set );
    printTags();
}

void TagObject::removeTag( GluonCore::GluonObject* object )
{
    QMetaProperty property = object->metaObject()->property( 0 );
    QString objectname = property.read( object ).toString();
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

QList< QString > TagObject::getTags( GluonCore::GluonObject* object )
{
    QMetaProperty property = object->metaObject()->property( 0 );
    QString objectname = property.read( object ).toString();
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
        cout << i.key() << ': ';
        foreach( QString ob, i.value() )
            cout << ob << ' ';
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
        out << i.key() << ' ' << QStringList( i.value().toList() ).join(" ") << '\n';
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
    QString line;
    while( ( line = in.readLine() ) != QString::Null )
    {
        QList< QString > list = line.split(" ");
        QString key = list.first();
        list.pop_front();
        this->tags.insert( key, list );
    }
    return true;
}
#include "tagobject.moc"
#include "tagobject.h"

#include <QMetaProperty>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, TagObject )

TagObject::TagObject()
{
    this->tags.clear();
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
}

QList< QString > TagObject::getObjects( QString tag )
{
    return this->tags[ tag ].toList();
}

QList< QString > TagObject::getTags( GluonCore::GluonObject* object )
{
    QMetaProperty property = object->metaObject()->property( 0 );
    QString objectname = property.read( object ).toString();
    QList< QString> list;
    for(QHash<QString, QSet<QString> >::iterator i = this->tags.begin(); i != this->tags.end(); ++i)
        if( i.value().contains( objectname ) >= 0 )
            list.append( i.key() );
    return list;
}

#include "tagobject.moc"
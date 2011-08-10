/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#include "gdlhandler.h"

#include "gluonobject.h"
#include "gluonobjectfactory.h"
#include "debughelper.h"

#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QMetaProperty>
#include <QtCore/QUrl>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( GDLHandler )

GDLHandler::GDLHandler( QObject* parent )
    : GluonCore::Singleton< GluonCore::GDLHandler >( parent )
{
}

GDLHandler::~GDLHandler()
{
}

GluonObject*
GDLHandler::instantiateObject( QString className )
{
    GluonObject* newObject = GluonObjectFactory::instance()->instantiateObjectByName( className );
    if( !newObject )
        newObject = new GluonObject();

    return newObject;
}

GluonObject*
GDLHandler::createObject( QStringList objectStringList, QObject* parent )
{
    DEBUG_BLOCK
    GluonObject* createdObject = 0;
    int index = 0;
    QString currentPropertyName;
    foreach( const QString & item, objectStringList )
    {
        switch( index )
        {
            case 0:
            {
                // Object type
                createdObject = instantiateObject( item );
                GluonObject* gluonObj = qobject_cast<GluonObject*>( parent );
                if( gluonObj )
                {
                    gluonObj->addChild( createdObject );
                }
                else
                {
                    createdObject->setParent( parent );
                }
            }
            //DEBUG_TEXT(QString("Instantiated object of type %1").arg(createdObject->metaObject()->className()))
            break;
            case 1:
                // Object name
                createdObject->setName( item );
                break;
            default:
                // Everything else
                if( currentPropertyName.isEmpty() )
                {
                    if( item.startsWith( '{' ) )
                    {
                        // Items are parented automatically - see case 0 above
                        QList<GluonObject*> childList = parseGDL( item, item.length(), createdObject );
                    }
                    else
                    {
                        currentPropertyName = item;
                    }
                }
                else
                {
                    // Set the property with the current string as the value, and finally clear the property name
                    createdObject->setPropertyFromString( currentPropertyName, item );
                    currentPropertyName.clear();
                }
                break;
        }
        ++index;
    }
    return createdObject;
}

QList<QStringList>
GDLHandler::tokenizeObject( QString objectString )
{
    QList<QStringList> tokenizedObject;

    bool inItem = false;
    bool inObjectDefinition = false;
    bool inObjectName = false;
    bool inObjectType = false;

    bool inPropertyName = false;
    bool inPropertyValue = false;
    bool multilineProperty = false;
    bool inChild = false;
    bool childEnded = false;

    bool beingEscaped = false;
    int extraBracketCounter = 0;
    QString currentString;
    QStringList currentItem;

    QString::const_iterator i;
    for( i = objectString.begin(); i != objectString.end(); ++i )
    {
        if( ( *i ) == '#' )
        {
            ++i;
            while( ( *i ) != '\n' ) ++i;
            continue;
        }

        if( !inItem )
        {
            if( ( *i ) == '{' )
            {
                inItem = true;
            }
        }
        else
        {
            if( !inPropertyValue && !inPropertyName && !inChild && !inObjectDefinition )
            {
                if( !currentString.isEmpty() )
                {
                    currentItem.append( currentString.trimmed() );
                    currentString.clear();
                }

                // Ignore whitespace as instructed, rar!
                if( !i->isSpace() )
                {
                    if( ( *i ) == '}' )
                    {
                        // Once we hit an end, we should stop looking at this item
                        // In other words - add the item to the list of items and make a new stringlist to work on...
                        QStringList theItem( currentItem );
                        tokenizedObject.append( theItem );
                        currentItem.clear();
                    }
                    else if( ( *i ) == '{' )
                    {
                        // If we hit a start while already inside an item, we should simply start adding stuff
                        // until we hit the correct ending again
                        inChild = true;
                    }
                    else
                    {
                        // Once you hit something, start reading the object definition
                        inObjectDefinition = true;
                    }
                }
            }

            if( inObjectDefinition )
            {
                if( !inPropertyName && !inObjectName && !inObjectType )
                {
                    // Ignore spaces between the start { and the object type
                    if( !i->isSpace() )
                        inObjectType = true;
                }

                if( inObjectType )
                {
                    if( ( *i ) == '(' )
                    {
                        currentItem.append( currentString.trimmed() );
                        currentString.clear();
                        inObjectType = false;
                        inObjectName = true;
                    }
                    else
                    {
                        currentString += i->unicode();
                    }
                }
                else if( inObjectName )
                {
                    if( ( *i ) == ')' )
                    {
                        currentItem.append( currentString.trimmed() );
                        currentString.clear();
                        inObjectName = false;
                        inPropertyName = true;
                    }
                    else
                    {
                        currentString += i->unicode();
                    }
                }
                else if( inPropertyName )
                {
                    if( !i->isSpace() )
                        inObjectDefinition = false;
                }
            }
            else if( inChild )
            {
                if( childEnded )
                {
                    if( !i->isSpace() )
                    {
                        inChild = false;
                    }
                }
                else
                {
                    if( i->toLower() == '\\' && !beingEscaped )
                    {
                        beingEscaped = true;
                    }
                    else
                    {
                        currentString += i->unicode();
                        if( !beingEscaped )
                        {
                            if( ( *i ) == '{' )
                            {
                                ++extraBracketCounter;
                            }

                            if( ( *i ) == '}' )
                            {
                                --extraBracketCounter;
                                if( extraBracketCounter == -1 )
                                {
                                    // Ready to look for more values!
                                    extraBracketCounter = 0;
                                    childEnded = true;
                                    inPropertyName = true;
                                    currentItem.append( '{' + currentString.trimmed() );
                                    currentString.clear();
                                }
                            }
                        }
                        else
                        {
                            beingEscaped = false;
                        }
                    }
                }
            }

            if( !inObjectDefinition && !inChild )
            {
                if( inPropertyName )
                {
                    // Read name until we hit a space, and after that, start reading the value...
                    if( ( *i ) == '{' )
                    {
                        inChild = true;
                        childEnded = false;
                    }
                    else if( ( *i ) == '}' )
                    {
                        inPropertyName = false;
                        // Rewind the pointer to make it possible to catch the end brackets above
                        --i;
                    }
                    else if( !i->isSpace() )
                    {
                        currentString += i->unicode();
                    }
                    else
                    {
                        currentItem.append( currentString.trimmed() );
                        currentString.clear();
                        inPropertyName = false;
                        inPropertyValue = true;
                    }
                }
                else if( inPropertyValue )
                {
                    if( *i == '<' && *( i + 1 ) == '<' && *( i + 2 ) == '<' )
                    {
                        multilineProperty = !multilineProperty;
                        i = i + 2;
                    }
                    else if( ( *i ) == '\\' && !beingEscaped )
                    {
                        beingEscaped = true;
                    }
                    else
                    {
                        // Read the value until the value ends!
                        currentString += i->unicode();
                        if( !beingEscaped && !multilineProperty && ( *i ) == ')' )
                        {
                            currentItem.append( currentString.trimmed() );
                            currentString.clear();
                            inPropertyValue = false;
                            inPropertyName = true;
                            // Make sure you don't start looking for property names again until you've got something that
                            // isn't a space (since the propertyname search doesn't know how to handle that)
                            forever
                            {
                                if( i == objectString.end() )
                                    break;
                                ++i;
                                if( ( *i ) == '#' )
                                {
                                    ++i;
                                    while( ( *i ) != '\n' ) ++i;
                                    continue;
                                }
                                if( i->isSpace() )
                                    continue;
                                --i;
                                break;
                            }
                        }
                        beingEscaped = false;
                    }
                }
            }
        }
    }

    return tokenizedObject;
}

QList<GluonObject*>
GDLHandler::parseGDL( const QString data, qint64 size, QObject* parent )
{
    QList<GluonObject*> thisObjectList;

    QList<QStringList> tokenizedObject = tokenizeObject( data );

    foreach( const QStringList & item, tokenizedObject )
    {
        GluonObject* currentObject = createObject( item, parent );
        thisObjectList.append( currentObject );
        currentObject->sanitize();
    }

    return thisObjectList;
}

QList<GluonObject*>
GDLHandler::parseGDL( const QString& fileName, QObject* parent )
{
    qint64 size = 0;

    QFile file( fileName );
    if( !file.open( QIODevice::ReadOnly ) )
        return QList<GluonObject*>();

    QByteArray data = file.readAll();
    file.close();

    return parseGDL( data, size, parent );
}

QList<GluonObject*>
GDLHandler::parseGDL( const QUrl& fileUrl, QObject* parent )
{
    return parseGDL( fileUrl.toLocalFile(), parent );
}

QString
GDLHandler::serializeGDL( QList<const GluonObject*> serializeThis )
{
    QString serializedData;

    foreach( const GluonObject * theObject, serializeThis )
    serializedData.append( toGDL( theObject ) );

    return serializedData;
}

QString
GDLHandler::childrenToGDL( const GluonObject* gluonObject, int indentLevel ) const
{
    QString serializedChildren;

    // Run through all the children to get them as well
    foreach( QObject * child, gluonObject->children() )
    {
        GluonObject* theChild = qobject_cast<GluonObject*>( child );
        if( theChild )
            serializedChildren.append( toGDL( theChild, indentLevel ) );
    }

    return serializedChildren;
}

QString
GDLHandler::propertiesToGDL( const GluonObject* gluonObject, int indentLevel ) const
{
    DEBUG_BLOCK
    QString serializedObject;

    QString indentChars( indentLevel * 4, ' ' );

    // Get all the normally defined properties
    const QMetaObject* metaobject = gluonObject->metaObject();
    int count = metaobject->propertyCount();
    if( count == 2 )
    {
        //DEBUG_TEXT(QString("No normal properties"))
    }
    for( int i = 0; i < count; ++i )
    {
        QMetaProperty metaproperty = metaobject->property( i );
        const QString theName( metaproperty.name() );
        if( theName == "objectName" || theName == "name" || !metaproperty.isWritable() )
            continue;
        serializedObject.append( gluonObject->stringFromProperty( theName, indentChars ) );
    }

    // Then get all the dynamic ones (in case any such exist)
    QList<QByteArray> propertyNames = gluonObject->dynamicPropertyNames();
    if( propertyNames.length() == 0 )
    {
        //DEBUG_TEXT(QString("No dynamic properties"))
    }
    foreach( const QByteArray & propName, propertyNames )
    {
        const QString theName( propName );
        serializedObject.append( gluonObject->stringFromProperty( theName, indentChars ) );
    }

    return serializedObject;
}

QString
GDLHandler::toGDL( const GluonObject* gluonObject, int indentLevel ) const
{
    QString serializedObject;
    //DEBUG_TEXT(QString("Serializing object named %1").arg(this->name()))
    //DEBUG_TEXT(QString("With %1 Children").arg(children().size()))

    QString indentChars( indentLevel * 4, ' ' );

    // Only jump to net line in case we are inside another object
    if( indentLevel > 0 )
        serializedObject.append( '\n' );

    QString minimalClassName( gluonObject->metaObject()->className() );
    if( QString( gluonObject->metaObject()->className() ).startsWith( QString( "Gluon::" ) ) )
        minimalClassName = minimalClassName.mid( 7 );
    serializedObject.append( QString( "%1{ %2(%3)" ).arg( indentChars ).arg( minimalClassName ).arg( gluonObject->name() ) );

    serializedObject.append( propertiesToGDL( gluonObject, indentLevel + 1 ) );
    if( gluonObject->shouldSerializeChildren( ) )
        serializedObject.append( childrenToGDL( gluonObject, indentLevel + 1 ) );

    return QString( "%1\n%2}" ).arg( serializedObject ).arg( indentChars );
}

#include "gdlhandler.moc"

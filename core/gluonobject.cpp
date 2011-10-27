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
#include "gluonobject.h"

#include "debughelper.h"
#include "gluonvarianttypes.h"
#include "metainfo.h"

#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtCore/QMetaClassInfo>
#include <QtCore/QSizeF>

REGISTER_OBJECTTYPE( GluonCore, GluonObject )

using namespace GluonCore;

Q_DECLARE_METATYPE( QList<int> )

class GluonObject::Private
{
    public:
        Private() : gameProject( 0 ),  metaInfo( 0 )
        { }

        QString name;
        GluonObject* gameProject;
        MetaInfo* metaInfo;
};

GluonObject::GluonObject( QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    qRegisterMetaType< QList<QUrl> >();
    // Get a nice name first time the object is created...
    QString theClassName( metaObject()->className() );
    if( theClassName.contains( ':' ) )
        setName( theClassName.right( theClassName.length() - theClassName.lastIndexOf( ':' ) - 1 ) );
    else
        setName( theClassName );
}

GluonObject::GluonObject( const QString& name, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    setName( name );
}

GluonObject::~GluonObject()
{
}

QString GluonObject::nameToObjectName( const QString& name )
{
    // Sanitize the object name to be an acceptable javascript object name.
    // While this is also done by the scripting engine, we use the object name for other things
    // as well, such as filenames etc
    QString theObjectName;
    QString::const_iterator i;
    for( i = name.constBegin(); i != name.constEnd(); ++i )
    {
        if( i->isLetterOrNumber() || *i == '_' )
            theObjectName.append( *i );
    }
    return theObjectName;
}

void
GluonObject::debug( const QString& debugText ) const
{
    DEBUG_BLOCK
    DEBUG_TEXT( debugText )
    emit showDebug( QString( "%1: %2" ).arg( fullyQualifiedName() ).arg( debugText ) );
}

void
GluonObject::debug( const QString& debugText, const QString& arg ) const
{
    DEBUG_BLOCK
    DEBUG_TEXT2( debugText, arg )
    emit showDebug( QString( "%1: %2" ).arg( fullyQualifiedName() ).arg( debugText.arg( arg ) ) );
}

GluonObject*
GluonObject::clone() const
{
    const QMetaObject* metaObj = metaObject();
    if( !metaObj )
        debug( QString( "Failed to get the meta object for object %1" ).arg( fullyQualifiedName() ) );

    // Find my parent...
    GluonObject* parentObject = qobject_cast<GluonObject*>( parent() );
    if( !parentObject )
        return 0;

    return clone( parentObject );
}

GluonObject*
GluonObject::clone( GluonObject* parentObject ) const
{
    const QMetaObject* metaObj = metaObject();
    if( !metaObj )
        debug( QString( "Failed to get the meta object for object %1" ).arg( fullyQualifiedName() ) );

    GluonObject* newObject = GluonObjectFactory::instance()->instantiateObjectByName( metaObj->className() );
    parentObject->addChild( newObject );

    // Clone all the children
    foreach( QObject * child, children() )
    {
        GluonObject* childObject = qobject_cast<GluonObject*>( child );
        if( childObject )
        {
            childObject->clone( newObject );
        }
    }

    // Copy over the values from pre-defined properties
    int count = metaObj->propertyCount();
    for( int i = 0; i < count; ++i )
    {
        QMetaProperty metaproperty = metaObj->property( i );
        newObject->setProperty( metaproperty.name(), metaproperty.read( this ) );
    }

    // Copy values from dynamic properties
    QList<QByteArray> propertyNames = dynamicPropertyNames();
    foreach( const QByteArray & propName, propertyNames )
    {
        newObject->setProperty( propName, property( propName ) );
    }

    // TODO: Clones with properties pointing to children should point to new children rather than the old children

    // In case any object is doing something clever with its children, make sure it's allowed to do that on cloning as well
    newObject->postCloneSanitize();
    return newObject;
}

void
GluonObject::sanitize()
{
    foreach( QObject * child, children() )
    {
        if( qobject_cast<GluonObject*>( child ) )
        {
            qobject_cast<GluonObject*>( child )->sanitize();
        }
    }
}

GluonObject*
GluonObject::gameProject() const
{
    return d->gameProject;
}

void
GluonObject::setGameProject( GluonObject* newGameProject )
{
    d->gameProject = newGameProject;

    foreach( QObject * child, children() )
    {
        GluonObject* obj = qobject_cast<GluonObject*>( child );
        if( obj )
            obj->setGameProject( newGameProject );
    }
}

QString
GluonObject::name() const
{
    return d->name;
}

const QStringList
GluonObject::supportedMimeTypes() const
{
    // We return an empty list, as the Asset class itself supports no mimetypes
    return QStringList();
}

void
GluonObject::setName( const QString& newName )
{
    // Store the old name, so we can emit a signal with it at the end
    QString oldName = d->name;

    // Don't allow setting the name to nothing
    if( newName.isEmpty() )
        return;

    // This is kinda nasty, but it's the easiest way to not clash with ourselves ;)
    d->name = "";

    QString theName( newName );
    // Fix up the name to not include any '/' (this would screw up the fullyQualifiedName)
    theName.replace( '/', ' ' );
    // Ensure we have no newlines and no consecutive whitespace
    theName = theName.simplified();

    // Make sure we don't set a name on an object which is already used!
    if( parent() )
    {
        bool nameIsOK = true;
        int addedNumber = 0;
        QObjectList theChildren = parent()->children();
        do
        {
            addedNumber++;
            nameIsOK = true;
            foreach( QObject * child, theChildren )
            {
                GluonObject* theChild = qobject_cast<GluonObject*>( child );
                if( theChild )
                {
                    if( theChild->name().toLower() == theName.toLower() )
                    {
                        theName = QString( newName + " %1" ).arg( addedNumber );
                        // Fix up the name to not include any '/' (this would screw up the
                        // fullyQualifiedName)
                        theName.replace( '/', ' ' );
                        // Ensure we have no newlines and no consecutive whitespace
                        theName = theName.simplified();
                        nameIsOK = false;
                        break;
                    }
                }
            }
        }
        while( !nameIsOK );
    }
    d->name = theName;
    emit nameChanged(oldName, theName);

    setObjectName( theName );
}

QString
GluonObject::fullyQualifiedName() const
{
    GluonObject* theParent = qobject_cast<GluonObject*>( parent() );
    if( theParent )
        return QString( "%1/%2" ).arg( theParent->fullyQualifiedName() ).arg( name() );
    return name();
}

QString GluonObject::qualifiedName(GluonObject* localRoot) const
{
    GluonObject* theParent = qobject_cast<GluonObject*>( parent() );
    if( theParent )
    {
        if( theParent == localRoot )
            return "";
        return QString( "%1/%2" ).arg( theParent->fullyQualifiedName() ).arg( name() );
    }
    return name();
}

GluonCore::GluonObject*
GluonObject::findItemByName( QString qualifiedName ) const
{
    /*DEBUG_BLOCK
    DEBUG_TEXT(QString("Looking up %1").arg(qualifiedName))*/
    QStringList names = qualifiedName.split( '/' );
    if( names.at( 0 ) == name() )
        names.removeFirst();
    return findItemByNameInObject( names, this );
}

GluonObject*
GluonObject::root()
{
    if( qobject_cast<GluonObject*>( parent() ) )
        return qobject_cast<GluonObject*>( parent() )->root();
    return this;
}

void GluonObject::addChildAt(GluonObject* child, int position)
{
    QList<QObject*> latterChildren;

    // First move the children from position and forwards out of the current object
    QList<QObject*> currentChildren = children();
    if(position < currentChildren.count())
    {
        for(int i = position; i < currentChildren.count(); ++i)
        {
            latterChildren.append(currentChildren.at(i));
            removeChild( qobject_cast<GluonObject*>(currentChildren.at(i)));
        }
    }

    // Then add the new object
    addChild(child);

    // Finally add the existing objects
    QList<QObject*>::iterator i;
    for(i = latterChildren.begin(); i != latterChildren.end(); ++i)
        addChild( qobject_cast<GluonObject*>(*i) );
}

void GluonObject::addChild( GluonObject* child )
{
    GluonObject* parent = qobject_cast<GluonObject*>( child->parent() );
    if( parent )
    {
        parent->removeChild( child );
        disconnect( child, SIGNAL( showDebug( const QString& ) ), parent, SIGNAL( showDebug( const QString& ) ) );
    }

    child->setParent( this );

    //Make sure to update the child's name to avoid name conflicts.
    child->setName( child->name() );
    connect( child, SIGNAL( showDebug( const QString& ) ), SIGNAL( showDebug( const QString& ) ) );
}

GluonObject* GluonObject::child( int index ) const
{
    return qobject_cast<GluonObject*>( children().at( index ) );
}

GluonObject* GluonObject::child( const QString& name ) const
{
    foreach( QObject * child, children() )
    {
        GluonObject* obj = qobject_cast<GluonObject*>( child );
        if( obj && obj->name() == name )
            return obj;
    }
    return 0;
}

bool GluonObject::removeChild( GluonObject* child )
{
    child->setParent( 0 );
    return true;
}

GluonObject*
GluonObject::findItemByNameInObject( QStringList qualifiedName, const GluonCore::GluonObject* object )
{
    //DEBUG_FUNC_NAME
    DEBUG_BLOCK
    GluonObject* foundChild = 0;

    QString lookingFor( qualifiedName[0] );
    qualifiedName.removeFirst();

    //DEBUG_TEXT(QString("Looking for object of name %1 in the object %2").arg(lookingFor).arg(object->name()));
    foreach( QObject * child, object->children() )
    {
        if( qobject_cast<GluonObject*>( child ) )
        {
            if( qobject_cast<GluonObject*>( child )->name() == lookingFor )
            {
                foundChild = qobject_cast<GluonObject*>( child );
                break;
            }
        }
    }

    // checking for nullity to guard against trying to go into non-existent sub-trees
    if( foundChild != 0 )
    {
        if( qualifiedName.count() > 0 )
        {
            //DEBUG_TEXT(QString("Found child, recursing..."))
            return GluonObject::findItemByNameInObject( qualifiedName, foundChild );
        }
        else
        {
            //DEBUG_TEXT(QString("Found child!"))
        }
    }
    else
    {
        QString childNames;
        foreach( QObject * child, object->children() )
        {
            childNames.append( child->objectName() ).append( ", " );
        }
        /*DEBUG_TEXT( QString( "Did not find child - bailing out! Was looking for object named %1 in object named %2. Available children are: %3" )
                    .arg( lookingFor )
                    .arg( object->fullyQualifiedName() )
                    .arg( childNames )
                  );*/
    }

    return foundChild;
}

MetaInfo*
GluonObject::metaInfo()
{
    if( !d->metaInfo )
    {
        d->metaInfo = new MetaInfo( this );
        populateMetaInfo( d->metaInfo );
    }
    return d->metaInfo;
}

bool
GluonObject::hasMetaInfo() const
{
    if( d->metaInfo )
        return true;
    return false;
}

bool
GluonObject::shouldSerializeChildren() const
{
    return true;
}

void
GluonObject::handleMessage( const QString& /* message */ )
{
}

#include "gluonobject.moc"

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
#include "gluonobjectprivate.h"
#include "debughelper.h"
#include "gluonvarianttypes.h"
#include "metainfo.h"

#include <QtCore/QVariant>
#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtCore/QDebug>
#include <QtCore/QMetaClassInfo>
#include <QSizeF>

REGISTER_OBJECTTYPE( GluonCore, GluonObject )

using namespace GluonCore;

static int qlist_qurl_typeID = qRegisterMetaType< QList<QUrl> >();

GluonObject::GluonObject( QObject* parent )
    : QObject( parent )
    , d( new GluonObjectPrivate() )
{
    // Get a nice name first time the object is created...
    QString theClassName( metaObject()->className() );
    if( theClassName.contains( ':' ) )
        setName( theClassName.right( theClassName.length() - theClassName.lastIndexOf( ':' ) - 1 ) );
    else
        setName( theClassName );
}

GluonObject::GluonObject( const QString& name, QObject* parent )
    : QObject( parent )
    , d( new GluonObjectPrivate() )
{
    setName( name );
}

GluonObject::GluonObject( const GluonCore::GluonObject& rt )
    : d( new GluonObjectPrivate( *rt.d ) )
{
}

GluonObject::~GluonObject()
{
}

void
GluonObject::debug( const QString& debugText ) const
{
    DEBUG_BLOCK
    DEBUG_TEXT( debugText );
    emit showDebug( QString( "%1: %2" ).arg( fullyQualifiedName() ).arg( debugText ) );
}

void
GluonObject::debug( const QString& debugText, const QString& arg ) const
{
    DEBUG_BLOCK
    DEBUG_TEXT2( debugText, arg );
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

#ifdef __GNUC__
#warning Clones with properties pointing to children should point to new children rather than the old children
#endif

    // In case any object is doing something clever with its children, make sure it's allowed to do that on cloning as well
    newObject->postCloneSanitize();
    return newObject;
}

void
GluonObject::sanitize()
{
    DEBUG_BLOCK
    //    DEBUG_TEXT(QString("Sanitizing the object %1 with %2 children").arg(this->fullyQualifiedName()).arg(this->children().count()));

    foreach( QObject * child, children() )
    {
        // The way assets handle their data will often cause the existence of children
        // which are not GluonObjects, and we should of course be handling that
        if( qobject_cast<GluonObject*>( child ) )
        {
            qobject_cast<GluonObject*>( child )->sanitize();
        }
    }

    // Make sure the GameProject is set... Iterate upwards until you either reach
    // the first GameProject instance, or you run into a parent which is null
    if( !gameProject() )
    {
        QObject* currentParent = parent();
        while( currentParent )
        {
            if( currentParent->metaObject()->className() == QString( "GluonEngine::GameProject" ) )
            {
                setGameProject( qobject_cast<GluonObject*>( currentParent ) );
                break;
            }
            currentParent = currentParent->parent();
        }
    }

    // Run through all properties, check whether they are set to the correct
    // value. If they should be pointing to something, make them!
    // (e.g. GameObject(Projectname.Something))
    QStringList objectTypeNames = GluonObjectFactory::instance()->objectTypeNames();

    const QMetaObject* metaobject = metaObject();
    if( metaobject == 0 )
        return;
    int count = metaobject->propertyCount();
    for( int i = 0; i < count; ++i )
    {
        QMetaProperty metaproperty = metaobject->property( i );

        // This is really only relevant if the property value is a string.
        // If it is not, what happens below is irrelevant
        if( metaproperty.type() != QVariant::String )
            continue;

        const QString theName( metaproperty.name() );
        if( theName == "objectName" || theName == "name" )
            continue;

        QString theValue( metaproperty.read( this ).toString() );

        // If we haven't got a reference, don't bother to look
        if( !theValue.endsWith( ')' ) )
            continue;

        //DEBUG_TEXT(QString("Attempting to sanitize property %1 with current value %2").arg(metaproperty.name()).arg(theValue));

        sanitizeReference( theName, theValue );
    }

    // Then get all the dynamic ones (in case any such exist)
    QList<QByteArray> propertyNames = dynamicPropertyNames();
    foreach( const QByteArray & propName, propertyNames )
    {
        const QString theName( propName );
        if( theName == "objectName" || theName == "name" )
            continue;

        // This is really only relevant if the property value is a string.
        // If it is not, what happens below is irrelevant
        if( property( propName ).type() != QVariant::String )
            continue;

        QString theValue( property( propName ).toString() );

        // If we haven't got a reference, don't bother to look
        if( !theValue.endsWith( ')' ) )
            continue;

        //DEBUG_TEXT(QString("Attempting to sanitize property %1 (dynamic) with current value %2").arg(QString(propName)).arg(theValue));

        sanitizeReference( theName, theValue );
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

    const QObjectList& allChildren = children();
    foreach( QObject * child, allChildren )
    {
        GluonObject* gobj = qobject_cast<GluonObject*>( child );
        if( gobj )
            gobj->setGameProject( newGameProject );
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
    // Don't allow setting the name to nothing
    if( newName.isEmpty() )
        return;

    // This is kinda nasty, but it's the easiest way to not clash with ourselves ;)
    d->name = "";

    QString theName( newName );
    // Fix up the name to not include any '/' (this would screw up the fullyQualifiedName)
    theName.replace( '/', ' ' );

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
                    if( theChild->name() == theName )
                    {
                        theName = QString( newName + " %1" ).arg( addedNumber );
                        nameIsOK = false;
                        break;
                    }
                }
            }
        }
        while( !nameIsOK );
    }
    d->name = theName;
    setObjectName( d->name );
}

QString
GluonObject::fullyQualifiedName() const
{
    QString theName( name() );
    if( qobject_cast<GluonObject*>( parent() ) )
        theName = QString( "%1/%2" ).arg( qobject_cast<GluonObject*>( parent() )->fullyQualifiedName() ).arg( theName );
    return theName;
}

QString
GluonObject::fullyQualifiedFileName() const
{
    QString qualifiedName = fullyQualifiedName();
    QString ext;
    if( qualifiedName.contains( '.' ) )
    {
        ext = qualifiedName.section( '.', -1 ).toLower();
        qualifiedName = qualifiedName.left( qualifiedName.lastIndexOf( '.' ) ).toLower();
    }

    //Filter out invalid characters for filenames
    QRegExp rx( "[\\/\\\\\\:\\.,\\* ]" );
    qualifiedName.replace( rx, "_" );
    if( !ext.isEmpty() )
        qualifiedName.append( '.' + ext );

    return qualifiedName;
}

GluonCore::GluonObject*
GluonObject::findItemByName( QString qualifiedName )
{
    /*DEBUG_BLOCK
    DEBUG_TEXT(QString("Looking up %1").arg(qualifiedName));*/
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

void GluonObject::addChild( GluonObject* child )
{
    GluonObject* parent = qobject_cast<GluonObject*>( child->parent() );
    if( parent )
    {
        parent->removeChild( child );
    }

    child->setParent( this );
    child->setName( child->name() );
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

void
GluonObject::setPropertyFromString( const QString& propertyName, const QString& propertyValue )
{
    DEBUG_BLOCK
    QVariant value;

    // propertyValue format is type(value)
    QRegExp rx( "((\\w*\\:*\\**)+)\\((.+)\\)" );
    rx.indexIn( propertyValue );

    QString theTypeName = rx.cap( 1 );
    QString theValue = rx.cap( 3 );

    if( theTypeName == "string" )
    {
        value = theValue;
    }
    else if( theTypeName == "bool" )
    {
        value = theValue == "true" ? true : false;
    }
    else if( theTypeName == "float" )
    {
        value = theValue.toFloat();
    }
    else if( theTypeName == "int" )
    {
        value = theValue.toInt();
    }
    else if( theTypeName == "uint" )
    {
        value = theValue.toUInt();
    }
    else if( theTypeName == "file" || theTypeName == "url" )
    {
        //DEBUG_TEXT(QString("Setting property from %1").arg(theTypeName));
        value = QVariant( QUrl( theValue ) );
    }
    else if( theTypeName == "vector2d" )
    {
        float x = 0.0f, y = 0.0f;

        QStringList splitValues = theValue.split( ';' );
        if( splitValues.length() > 0 )
        {
            x = splitValues.at( 0 ).toFloat();
            y = splitValues.at( 1 ).toFloat();
        }
        value = QVector2D( x, y );
    }
    else if( theTypeName == "vector3d" )
    {
        float x = 0.0f, y = 0.0f, z = 0.0f;

        QStringList splitValues = theValue.split( ';' );
        if( splitValues.length() > 0 )
        {
            x = splitValues.at( 0 ).toFloat();
            y = splitValues.at( 1 ).toFloat();
            z = splitValues.at( 2 ).toFloat();
        }
        value = QVector3D( x, y, z );
    }
    else if( theTypeName == "quaternion" )
    {
        float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

        QStringList splitValues = theValue.split( ';' );
        if( splitValues.length() > 0 )
        {
            x = splitValues.at( 0 ).toFloat();
            y = splitValues.at( 1 ).toFloat();
            z = splitValues.at( 2 ).toFloat();
            w = splitValues.at( 3 ).toFloat();
        }

        value = QQuaternion( w, x, y, z );
    }
    else if( theTypeName == "rgba" )
    {
        int r = 0, g = 0, b = 0, a = 0;
        QStringList splitValues = theValue.split( ';' );
        if( splitValues.length() > 0 )
            r = splitValues[0].toInt();
        if( splitValues.length() > 1 )
            g = splitValues[1].toInt();
        if( splitValues.length() > 2 )
            b = splitValues[2].toInt();
        if( splitValues.length() > 3 )
            a = splitValues[3].toInt();
        value = QColor( r, g, b, a );
    }
    else if( theTypeName == "size2d" )
    {
        float w = 0.0f;
        float h = 0.0f;

        QStringList splitValues = theValue.split( ';' );
        if( splitValues.length() > 0 )
        {
            w = splitValues.at( 0 ).toFloat();
            h = splitValues.at( 1 ).toFloat();
        }
        value = QSizeF( w, h );
    }
    else
    {
        // If all else fails, pass the value through verbatim
        value = propertyValue;

        //Set a sanitizable property
        setProperty( ( propertyName + "_sanitizable" ).toUtf8(), value );
        return;
    }

    setProperty( propertyName.toUtf8(), value );
}

QString
GluonObject::stringFromProperty( const QString& propertyName, const QString& indentChars ) const
{
    DEBUG_BLOCK
    QString value;

    QVariant theValue = property( propertyName.toUtf8() );

    QColor theColor;
    QVector3D theVector;
    QQuaternion theQuat;
    switch( theValue.type() )
    {
            /*case QVariant::UserType:
                DEBUG_TEXT("UserType detected");

                break;*/
        case QVariant::String:
            if( !theValue.toString().isEmpty() )
                value = "string(" + theValue.toString() + ')';
            break;
        case QVariant::Bool:
            value = QString( "bool(%1)" ).arg( theValue.toString() );
            break;
        case 135:
        case QVariant::Double:
            if( theValue.toDouble() )
                value = QString( "float(%1)" ).arg( theValue.toDouble() );
            break;
        case QVariant::Vector3D:
            theVector = theValue.value<QVector3D>();
            value = QString( "vector3d(%1;%2;%3)" ).arg( theVector.x() ).arg( theVector.y() ).arg( theVector.z() );
            break;
        case QVariant::Quaternion:
            theQuat = theValue.value<QQuaternion>();
            value = QString( "quaternion(%1;%2;%3;%4)" ).arg( theQuat.x() ).arg( theQuat.y() ).arg( theQuat.z() ).arg( theQuat.scalar() );
            break;
        case QVariant::Int:
            if( theValue.toInt() )
                value = QString( "int(%1)" ).arg( theValue.toInt() );
            break;
        case QVariant::UInt:
            if( theValue.toUInt() )
                value = QString( "uint(%1)" ).arg( theValue.toUInt() );
            break;
        case QVariant::Size:
        case QVariant::SizeF:
            value = QString( "size2d(%1;%2)" ).arg( theValue.toSizeF().width() ).arg( theValue.toSizeF().height() );
            break;
        case QVariant::PointF:
        case QVariant::Vector2D:
            value = QString( "vector2d(%1;%2)" ).arg( theValue.toPointF().x() ).arg( theValue.toPointF().y() );
            break;
        case QVariant::Color:
            theColor = theValue.value<QColor>();
            value = QString( "rgba(%1;%2;%3;%4)" ).arg( theColor.red() ).arg( theColor.green() ).arg( theColor.blue() ).arg( theColor.alpha() );
            break;
        case QVariant::Url:
            if( !theValue.toUrl().isEmpty() )
            {
                if( theValue.toString().startsWith( QLatin1String( "file" ) ) )
                    value = QString( "file(%1)" ).arg( theValue.toUrl().toString() );
                else
                    value = QString( "url(%1)" ).arg( theValue.toUrl().toString() );
            }
            break;
        default:
            GluonObject* theObject = GluonObjectFactory::instance()->wrappedObject( theValue );
            if( theObject )
            {
                value = QString( "%1(%2)" ).arg( theObject->metaObject()->className() ).arg( theObject->fullyQualifiedName() );
            }
            else
            {
                DEBUG_TEXT( QString( "Property %1 is of an unrecognised type %2" ).arg( propertyName ).arg( theValue.typeName() ) );
                value = theValue.toString();
            }
            break;
    }

    QString returnString = QString( "\n%1%2 %3" ).arg( indentChars ).arg( propertyName ).arg( value );

    if( value.isEmpty() )
    {
        value = QString( "(empty value)" );
        returnString.clear();
    }

    //DEBUG_TEXT(QString("Getting GDL string from property %1 of type %2 (%4) with value %3").arg(propertyName).arg(theValue.typeToName(theValue.type())).arg(value).arg(theValue.type()));

    return returnString;
}

GluonObject*
GluonObject::findItemByNameInObject( QStringList qualifiedName, GluonObject* object )
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
            //DEBUG_TEXT(QString("Found child, recursing..."));
            return GluonObject::findItemByNameInObject( qualifiedName, foundChild );
        }
        else
        {
            //DEBUG_TEXT(QString("Found child!"));
        }
    }
    else
    {
        DEBUG_TEXT( "Did not find child! Bailing out" );
    }

    return foundChild;
}


void
GluonObject::sanitizeReference( const QString& propName, const QString& propValue )
{
    QStringList objectTypeNames = GluonObjectFactory::instance()->objectTypeNames();
    // Yes, i know this is O(n*m) but it does not happen during gameplay
    foreach( const QString & typeName, objectTypeNames )
    {
        // Reset the value of this property to be a reference to GluonObjct
        // instance by that name, found in the project
        if( propValue.startsWith( typeName + '(' ) )
        {
            QString propertyName = propName;
            if( propertyName.contains( "_sanitizable" ) )
            {
                setProperty( propertyName.toUtf8(), QVariant() );
                propertyName = propertyName.left( propertyName.lastIndexOf( "_sanitizable" ) );
            }

            QString theReferencedName = propValue.mid( typeName.length() + 1, propValue.length() - ( typeName.length() + 2 ) );
            QVariant theReferencedObject;

            GluonObject* theObject = root()->findItemByName( theReferencedName );

            if( !theObject )
            {
                debug( QString( "Warning: Invalid reference for property %1 on object %2" ).arg( propertyName, name() ) );
                continue;
            }

            QMetaProperty property = metaObject()->property( metaObject()->indexOfProperty( propertyName.toUtf8() ) );
            theReferencedObject = GluonObjectFactory::instance()->wrapObject( QString( property.typeName() ), theObject );

            setProperty( propertyName.toUtf8(), theReferencedObject );
            break;
        }
    }
}

MetaInfo*
GluonObject::metaInfo()
{
    if( !d->metaInfo )
        d->metaInfo = new MetaInfo( this );
    return d->metaInfo;
}

bool
GluonObject::hasMetaInfo() const
{
    if( d->metaInfo )
        return true;
    return false;
}

void
GluonObject::handleMessage(const QString& message)
{
    Q_UNUSED(message)
}

#include "gluonobject.moc"

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#include "writer.h"

#include <QtCore/QSizeF>
#include <QtCore/QList>
#include <QtCore/QMetaProperty>
#include <QtCore/QDebug>
#include <QtGui/QColor>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/gluonobject.h>
#include <core/gluonobjectfactory.h>
#include <core/gluonvarianttypes.h>

using namespace GDL;
using namespace Eigen;

Writer::Writer()
{
    m_device = 0;
    m_indentLevel = 0;
}

Writer::~Writer()
{

}

void Writer::write( const GluonCore::GluonObjectList& objects, QIODevice* device)
{
    m_device = device;
    m_indentLevel = 0;

    foreach( GluonCore::GluonObject* object, objects )
    {
        writeObject( object );
    }
}

void Writer::writeObject( QObject* object)
{
    GluonCore::GluonObject* o = qobject_cast< GluonCore::GluonObject* >( object );
    if( !o )
        return;

    indent();
    m_device->write( QString( "{ %1(\"%2\")\n" ).arg( o->metaObject()->className() ).arg( o->name() ).toUtf8() );

    m_indentLevel++;

    const int numProperties = o->metaObject()->propertyCount();
    for( int i = 0; i < numProperties; ++i )
    {
        QMetaProperty property = o->metaObject()->property( i );
        writeProperty( property.name(), property.read( object)  );
    }

    QList<QByteArray> dynamicProperties = o->dynamicPropertyNames();
    foreach( const QByteArray& name, dynamicProperties )
    {
        writeProperty( QString( name ), o->property( name ) );
    }

    if( o->shouldSerializeChildren() )
    {
        foreach( QObject* child, o->children() )
        {
            writeObject( child );
        }
    }

    m_indentLevel--;
    indent();
    m_device->write( "}\n" );
}

void Writer::indent()
{
    m_device->write( QByteArray().fill( ' ', m_indentLevel * 4 ) );
}

void Writer::writeProperty(const QString& name, const QVariant& value)
{
    if( name == "name" || name == "objectName" || !value.isValid() )
        return;

    QString valueString = writePropertyValue( value );

    if( valueString.isEmpty() )
        return;

    indent();
    m_device->write( name.toUtf8() );
    m_device->write( " " );
    m_device->write( valueString.toUtf8() );
    m_device->write( "\n" );
}

QString Writer::writePropertyValue(const QVariant& value)
{
    QString valueString;
    switch( value.type() )
    {
        case QVariant::Bool:
            valueString = writeBoolValue( value );
            break;
        case QVariant::Int:
            valueString = writeIntValue( value );
            break;
        case QVariant::UInt:
            valueString = writeUIntValue( value );
            break;
        case QVariant::LongLong:
            valueString = writeLongLongValue( value );
            break;
        case GluonCore::VariantType::Float:
        case QVariant::Double:
            valueString = writeFloatValue( value );
            break;
        case QVariant::String:
            valueString = writeStringValue( value );
            break;
        case QVariant::Url:
            valueString = writeUrlValue( value );
            break;
        case QVariant::SizeF:
            valueString = writeSize2DValue( value );
            break;
        case QVariant::Color:
            valueString = writeRgbaValue( value );
            break;
        case QVariant::List:
            valueString = writeListValue( value );
            break;
        default:
            if( value.userType() == GluonCore::VariantType::Vector2f )
            {
                valueString = writeVector2DValue( value );
            }
            else if( value.userType() == GluonCore::VariantType::Vector3f )
            {
                valueString = writeVector3DValue( value );
            }
            else if( value.userType() == GluonCore::VariantType::Vector4f )
            {
                valueString = writeVector4DValue( value );
            }
            else if( value.userType() == GluonCore::VariantType::Quaternionf )
            {
                valueString = writeQuaternionValue( value );
            }
            else if( GluonCore::GluonObjectFactory::instance()->wrappedObject( value ) )
            {
                valueString = writeObjectValue( value );
            }
    }
    return valueString;
}

QString Writer::writeBoolValue( const QVariant& value)
{
    if( value.toBool() )
    {
        return QString( "bool(true)" );
    }
    else
    {
        return QString( "bool(false)" );
    }
}

QString Writer::writeIntValue(const QVariant& value)
{
    return QString( "int(%1)" ).arg( value.toInt() );
}

QString Writer::writeUIntValue(const QVariant& value)
{
    return QString( "uint(%1)" ).arg( value.toUInt() );
}

QString Writer::writeLongLongValue(const QVariant& value)
{
    return QString( "longlong(%1)" ).arg( value.toLongLong() );
}

QString Writer::writeFloatValue(const QVariant& value)
{
    return QString( "float(%1)" ).arg( value.toFloat() );
}

QString Writer::writeStringValue(const QVariant& value)
{
    if( value.toString().isEmpty() )
        return QString();

    return QString( "string(\"%1\")" ).arg( value.toString() );
}

QString Writer::writeUrlValue(const QVariant& value)
{
    if( value.toUrl().isEmpty() )
        return QString();

    return QString( "url(\"%1\")" ).arg( value.toUrl().toString() );
}

QString Writer::writeVector2DValue(const QVariant& value)
{
    Vector2f v = value.value< Vector2f >();
    return QString( "vector2d(%1;%2)" ).arg( v.x() ).arg( v.y() );
}

QString Writer::writeVector3DValue(const QVariant& value)
{
    Vector3f v = value.value< Vector3f >();
    return QString( "vector3d(%1;%2;%3)" ).arg( v.x() ).arg( v.y() ).arg( v.z() );
}

QString Writer::writeVector4DValue(const QVariant& value)
{
    Vector4f v = value.value< Vector4f >();
    return QString( "vector4d(%1;%2;%3;%4)" ).arg( v.x() ).arg( v.y() ).arg( v.z() ).arg( v.w() );
}

QString Writer::writeSize2DValue(const QVariant& value)
{
    QSizeF v = value.toSizeF();

    if( v.isNull() )
        return QString();

    return QString( "size2d(%1;%2)" ).arg( v.width() ).arg( v.height() );
}

QString Writer::writeRgbaValue(const QVariant& value)
{
    QColor v = value.value< QColor >();

    if( !v.isValid() )
        return QString();

    return QString( "rgba(%1;%2;%3;%4)" ).arg( v.red() ).arg( v.green() ).arg( v.blue() ).arg( v.alpha() );
}

QString Writer::writeQuaternionValue(const QVariant& value)
{
    Quaternionf v = value.value< Quaternionf >();

    if( v.coeffs() == Quaternionf::Identity().coeffs() )
        return QString();

    return QString( "quaternion(%1;%2;%3;%4)" ).arg( v.x() ).arg( v.y() ).arg( v.z() ).arg( v.w() );
}

QString Writer::writeObjectValue(const QVariant& value)
{
    GluonCore::GluonObject* obj = GluonCore::GluonObjectFactory::instance()->wrappedObject( value );
    if( !obj )
        return QString();

    return QString( "%1(\"%2\")" ).arg( obj->metaObject()->className() ).arg( obj->fullyQualifiedName() );
}

QString Writer::writeListValue(const QVariant& value)
{
    QVariantList list = value.toList();

    if( list.isEmpty() )
        return QString();

    QString listValue = QString("list([\n");
    foreach( const QVariant& val, list )
    {
        QString valueString = writePropertyValue( val );
        if( !valueString.isEmpty() )
            listValue.append( QString().fill( ' ', ( m_indentLevel + 1 ) * 4 ) + valueString + ";\n");
    }
    listValue += QString().fill( ' ', m_indentLevel * 4 ) + QString("])");
    return listValue;
}

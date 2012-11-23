/*************************************************************************
 * This file is part of the Gluon Development Platform
 *
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "objecttreebuilder.h"

#include <QtCore/QSizeF>
#include <QtCore/QMetaProperty>
#include <QtGui/QColor>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/gluonobject.h>
#include <core/gluonobjectfactory.h>
#include <core/debughelper.h>
#include <core/gluonvarianttypes.h>

#include <core/gdl/gdllexer.h>
#include <core/gdl/gdlparser.h>

using namespace GDL;
using namespace GluonCore;
using namespace Eigen;

class ObjectTreeBuilder::Private
{
    public:
        struct Reference
        {
            GluonObject* object;
            QString property;
            QString type;
            QString path;
        };

        Private() : currentObject( 0 ), inList( false ) { }

        QString textForToken(Lexer::Token token);
        QString stripQuotes(const QString& input);

        Lexer* lexer;
        QString content;

        QList<GluonObject*> objects;
        GluonObject* currentObject;
        GluonObject* project;
        GluonObject* parent;
        QString currentPropertyName;
        QVariant currentPropertyValue;
        bool inList;
        QVariantList list;

        QList<Reference> references;
};

ObjectTreeBuilder::ObjectTreeBuilder(Lexer* lexer, const QString& content, GluonObject* project, GluonObject* parent )
    : d(new Private)
{
    d->lexer = lexer;
    d->content = content;
    d->project = project;
    d->parent = parent;
}

ObjectTreeBuilder::~ObjectTreeBuilder()
{

}

QList< GluonObject* > ObjectTreeBuilder::objects()
{
    return d->objects;
}

void ObjectTreeBuilder::visitStart(StartAst* node)
{
    DefaultVisitor::visitStart(node);

    //Post-process references
    foreach( const Private::Reference& ref, d->references )
    {
        GluonObject* target = 0;

        // Check whether the path points into this GDL file
        bool isRelative = false;
        QString relativePath;
        if( d->parent )
        {
            QString refPathWithoutRoot = ref.path.section( '/', 1, -1 );
            QString parentPathWithoutRoot = d->parent->qualifiedName( d->parent->root() );
            if( refPathWithoutRoot.startsWith( parentPathWithoutRoot ) )
            {
                isRelative = true;
                relativePath = refPathWithoutRoot.remove( 0, parentPathWithoutRoot.length()+1 ); // +1 for the slash
            }
        }

        // now try to find the reference
        foreach( GluonObject* object, d->objects )
        {
            if( isRelative )
                target = object->findGlobalItemByName( relativePath );
            else
                target = object->findGlobalItemByName( ref.path );

            if( target )
                break;
        }

        if( !target )
        {
            target = d->project->findGlobalItemByName( ref.path );

            if( !target )
            {
                ref.object->debug("Warning: Invalid reference for property %1", ref.property);
                continue;
            }
        }

        QString type = ref.type;
        int propertyIndex = ref.object->metaObject()->indexOfProperty( ref.property.toUtf8() );
        if( propertyIndex != -1 )
            type = ref.object->metaObject()->property( propertyIndex ).typeName();

        if( !ref.object->setProperty( ref.property.toUtf8(), GluonCore::GluonObjectFactory::instance()->wrapObject( type, target ) ) )
        {
            if( propertyIndex != -1 )
                ref.object->debug( QString("Warning: Could not set property %1 on object %2").arg(ref.property, ref.object->fullyQualifiedName()) );
        }
    }

    //Allow subclasses to do their own post-processing as well
    foreach( GluonCore::GluonObject* object, d->objects )
    {
        object->sanitize();
    }
}

void ObjectTreeBuilder::visitObject(GDL::ObjectAst* node)
{
    QString type = d->textForToken(d->lexer->at(node->type));
    GluonObject* newObject = GluonObjectFactory::instance()->instantiateObjectByName( type );
    if( !newObject )
    {
        return;
    }

    if( !d->project )
    {
        d->project = newObject;
    }
    else
    {
        newObject->setGameProject( d->project );
    }


    newObject->setName( d->stripQuotes( d->textForToken( d->lexer->at( node->name ) ) ) );

    if(d->currentObject)
    {
        d->currentObject->addChild(newObject);
    }
    else
    {
        d->objects.append(newObject);
    }

    GluonObject* parent = d->currentObject;
    d->currentObject = newObject;

    GDL::DefaultVisitor::visitObject(node);

    d->currentObject = parent;
}

void ObjectTreeBuilder::visitProperty(GDL::PropertyAst* node)
{
    if(!d->currentObject)
    {
        qFatal("Cannot set properties on non-existing object");
        return;
    }

    d->currentPropertyName = d->textForToken(d->lexer->at(node->propertyName));

    GDL::DefaultVisitor::visitProperty(node);

    if(!d->currentPropertyValue.isNull())
    {
        d->currentObject->setProperty(d->currentPropertyName.toUtf8(), d->currentPropertyValue);
    }
}

void ObjectTreeBuilder::visitProperty_type(Property_typeAst* node)
{
    GDL::DefaultVisitor::visitProperty_type(node);

    if( d->inList )
        d->list.append( d->currentPropertyValue );
}

void ObjectTreeBuilder::visitList_type(GDL::List_typeAst* node)
{
    d->inList = true;
    d->list = QVariantList();
    GDL::DefaultVisitor::visitList_type(node);
    d->inList = false;
    d->currentPropertyValue = QVariant::fromValue( d->list );
}

void ObjectTreeBuilder::visitBoolean_type(GDL::Boolean_typeAst* node)
{
    Lexer::Token boolToken = d->lexer->at(node->value);
    d->currentPropertyValue = QVariant::fromValue<bool>(boolToken.kind == Parser::Token_TRUE_VALUE);
}

void ObjectTreeBuilder::visitInteger_type(GDL::Integer_typeAst* node)
{
    Lexer::Token intToken = d->lexer->at(node->value);
    d->currentPropertyValue = QVariant::fromValue<int>(d->textForToken(intToken).toInt());
}

void ObjectTreeBuilder::visitUnsigned_int_type(GDL::Unsigned_int_typeAst* node)
{
    Lexer::Token uintToken = d->lexer->at(node->value);
    d->currentPropertyValue = QVariant::fromValue<uint>(d->textForToken(uintToken).toUInt());
}

void ObjectTreeBuilder::visitLong_long_type(GDL::Long_long_typeAst* node)
{
    Lexer::Token longToken = d->lexer->at(node->value);
    d->currentPropertyValue = QVariant::fromValue<qlonglong>(d->textForToken(longToken).toLongLong());
}

void ObjectTreeBuilder::visitFloat_type(GDL::Float_typeAst* node)
{
    Lexer::Token floatToken = d->lexer->at(node->value);
    d->currentPropertyValue = QVariant::fromValue<float>(d->textForToken(floatToken).toFloat());
}

void ObjectTreeBuilder::visitString_type(GDL::String_typeAst* node)
{
    QString stringValue = d->stripQuotes( d->textForToken( d->lexer->at(node->value) ) );
    d->currentPropertyValue = QVariant::fromValue<QString>( stringValue );
}

void ObjectTreeBuilder::visitUrl_type(GDL::Url_typeAst* node)
{
    QString stringValue = d->stripQuotes( d->textForToken( d->lexer->at( node->path ) ) );
    d->currentPropertyValue = QVariant::fromValue<QUrl>(QUrl( stringValue ) );
}

void ObjectTreeBuilder::visitRgba_type(GDL::Rgba_typeAst* node)
{
    QColor color;
    Lexer::Token token = d->lexer->at(node->r);
    color.setRed(d->textForToken(token).toInt());
    token = d->lexer->at(node->g);
    color.setGreen(d->textForToken(token).toInt());
    token = d->lexer->at(node->b);
    color.setBlue(d->textForToken(token).toInt());
    token = d->lexer->at(node->a);
    color.setAlpha(d->textForToken(token).toInt());

    d->currentPropertyValue = QVariant::fromValue<QColor>(color);
}

void ObjectTreeBuilder::visitVector2d_type(GDL::Vector2d_typeAst* node)
{
    Vector2f vector;
    GDL::Lexer::Token token = d->lexer->at(node->x);
    vector(1) = d->textForToken(token).toFloat();
    token = d->lexer->at(node->y);
    vector(2) = d->textForToken(token).toFloat();

    d->currentPropertyValue = QVariant::fromValue<Vector2f>(vector);
}

void ObjectTreeBuilder::visitVector3d_type(GDL::Vector3d_typeAst* node)
{
    Vector3f vector;
    GDL::Lexer::Token token = d->lexer->at(node->x);
    vector(1) = d->textForToken(token).toFloat();
    token = d->lexer->at(node->y);
    vector(2) = d->textForToken(token).toFloat();
    token = d->lexer->at(node->z);
    vector(3) = d->textForToken(token).toFloat();

    d->currentPropertyValue = QVariant::fromValue<Vector3f>(vector);
}

void ObjectTreeBuilder::visitVector4d_type(GDL::Vector4d_typeAst* node)
{
    Vector4f vector;
    GDL::Lexer::Token token = d->lexer->at(node->x);
    vector(1) = d->textForToken(token).toFloat();
    token = d->lexer->at(node->y);
    vector(2) = d->textForToken(token).toFloat();
    token = d->lexer->at(node->z);
    vector(3) = d->textForToken(token).toFloat();
    token = d->lexer->at(node->w);
    vector(4) = d->textForToken(token).toFloat();

    d->currentPropertyValue = QVariant::fromValue<Vector4f>(vector);
}

void ObjectTreeBuilder::visitQuaternion_type(GDL::Quaternion_typeAst* node)
{
    Quaternionf quat;
    GDL::Lexer::Token token = d->lexer->at(node->x);
    quat.x() = d->textForToken(token).toFloat();
    token = d->lexer->at(node->y);
    quat.y() = d->textForToken(token).toFloat();
    token = d->lexer->at(node->z);
    quat.z() = d->textForToken(token).toFloat();
    token = d->lexer->at(node->w);
    quat.w() = d->textForToken(token).toFloat();

    d->currentPropertyValue = QVariant::fromValue<Quaternionf>(quat);
}

void ObjectTreeBuilder::visitSize2d_type(GDL::Size2d_typeAst* node)
{
    QSizeF size;
    GDL::Lexer::Token token = d->lexer->at(node->width);
    size.setWidth(d->textForToken(token).toFloat());
    token = d->lexer->at(node->height);
    size.setHeight(d->textForToken(token).toFloat());

    d->currentPropertyValue = QVariant::fromValue<QSizeF>(size);
}

void ObjectTreeBuilder::visitObject_type(GDL::Object_typeAst* node)
{
    QString type = d->textForToken( d->lexer->at( node->type ) );
    QString reference = d->stripQuotes( d->textForToken( d->lexer->at( node->value ) ) );

    Private::Reference ref = { d->currentObject, d->currentPropertyName, type, reference };
    d->references.append( ref );

    d->currentPropertyValue = QVariant();
}

QString ObjectTreeBuilder::Private::textForToken(KDevPG::Token token)
{
    return content.mid(token.begin, token.end - token.begin + 1);
}

QString ObjectTreeBuilder::Private::stripQuotes(const QString& input)
{
    QString retval = input;
    if(retval.at(0) == '"')
        retval = retval.remove(0, 1);
    if(retval.at(retval.size() - 1) == '"')
        retval = retval.remove(retval.size() - 1, 1);
    return retval;
}
